#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct input_pixel_processor {int dummy; } ;
struct dce_ipp {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  low_part; int /*<<< orphan*/  high_part; } ;
struct TYPE_4__ {int /*<<< orphan*/  INVERSE_TRANSPARENT_CLAMPING; int /*<<< orphan*/  ENABLE_MAGNIFICATION; } ;
struct TYPE_5__ {TYPE_1__ bits; } ;
struct dc_cursor_attributes {int color_format; TYPE_3__ address; scalar_t__ height; scalar_t__ width; TYPE_2__ attribute_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  CURSOR_2X_MAGNIFY ; 
 int /*<<< orphan*/  CURSOR_HEIGHT ; 
 int /*<<< orphan*/  CURSOR_MODE ; 
#define  CURSOR_MODE_COLOR_1BIT_AND 131 
#define  CURSOR_MODE_COLOR_PRE_MULTIPLIED_ALPHA 130 
#define  CURSOR_MODE_COLOR_UN_PRE_MULTIPLIED_ALPHA 129 
#define  CURSOR_MODE_MONO 128 
 int /*<<< orphan*/  CURSOR_SURFACE_ADDRESS ; 
 int /*<<< orphan*/  CURSOR_SURFACE_ADDRESS_HIGH ; 
 int /*<<< orphan*/  CURSOR_UPDATE_LOCK ; 
 int /*<<< orphan*/  CURSOR_WIDTH ; 
 int /*<<< orphan*/  CUR_COLOR1 ; 
 int /*<<< orphan*/  CUR_COLOR1_BLUE ; 
 int /*<<< orphan*/  CUR_COLOR1_GREEN ; 
 int /*<<< orphan*/  CUR_COLOR1_RED ; 
 int /*<<< orphan*/  CUR_COLOR2 ; 
 int /*<<< orphan*/  CUR_COLOR2_BLUE ; 
 int /*<<< orphan*/  CUR_COLOR2_GREEN ; 
 int /*<<< orphan*/  CUR_COLOR2_RED ; 
 int /*<<< orphan*/  CUR_CONTROL ; 
 int /*<<< orphan*/  CUR_INV_TRANS_CLAMP ; 
 int /*<<< orphan*/  CUR_SIZE ; 
 int /*<<< orphan*/  CUR_SURFACE_ADDRESS ; 
 int /*<<< orphan*/  CUR_SURFACE_ADDRESS_HIGH ; 
 int /*<<< orphan*/  CUR_UPDATE ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  REG_SET_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dce_ipp* TO_DCE_IPP (struct input_pixel_processor*) ; 

__attribute__((used)) static void dce_ipp_cursor_set_attributes(
	struct input_pixel_processor *ipp,
	const struct dc_cursor_attributes *attributes)
{
	struct dce_ipp *ipp_dce = TO_DCE_IPP(ipp);
	int mode;

	/* Lock cursor registers */
	REG_UPDATE(CUR_UPDATE, CURSOR_UPDATE_LOCK, true);

	/* Program cursor control */
	switch (attributes->color_format) {
	case CURSOR_MODE_MONO:
		mode = 0;
		break;
	case CURSOR_MODE_COLOR_1BIT_AND:
		mode = 1;
		break;
	case CURSOR_MODE_COLOR_PRE_MULTIPLIED_ALPHA:
		mode = 2;
		break;
	case CURSOR_MODE_COLOR_UN_PRE_MULTIPLIED_ALPHA:
		mode = 3;
		break;
	default:
		BREAK_TO_DEBUGGER(); /* unsupported */
		mode = 0;
	}

	REG_UPDATE_3(CUR_CONTROL,
		CURSOR_MODE, mode,
		CURSOR_2X_MAGNIFY, attributes->attribute_flags.bits.ENABLE_MAGNIFICATION,
		CUR_INV_TRANS_CLAMP, attributes->attribute_flags.bits.INVERSE_TRANSPARENT_CLAMPING);

	if (attributes->color_format == CURSOR_MODE_MONO) {
		REG_SET_3(CUR_COLOR1, 0,
			CUR_COLOR1_BLUE, 0,
			CUR_COLOR1_GREEN, 0,
			CUR_COLOR1_RED, 0);

		REG_SET_3(CUR_COLOR2, 0,
			CUR_COLOR2_BLUE, 0xff,
			CUR_COLOR2_GREEN, 0xff,
			CUR_COLOR2_RED, 0xff);
	}

	/*
	 * Program cursor size -- NOTE: HW spec specifies that HW register
	 * stores size as (height - 1, width - 1)
	 */
	REG_SET_2(CUR_SIZE, 0,
		CURSOR_WIDTH, attributes->width-1,
		CURSOR_HEIGHT, attributes->height-1);

	/* Program cursor surface address */
	/* SURFACE_ADDRESS_HIGH: Higher order bits (39:32) of hardware cursor
	 * surface base address in byte. It is 4K byte aligned.
	 * The correct way to program cursor surface address is to first write
	 * to CUR_SURFACE_ADDRESS_HIGH, and then write to CUR_SURFACE_ADDRESS
	 */
	REG_SET(CUR_SURFACE_ADDRESS_HIGH, 0,
		CURSOR_SURFACE_ADDRESS_HIGH, attributes->address.high_part);

	REG_SET(CUR_SURFACE_ADDRESS, 0,
		CURSOR_SURFACE_ADDRESS, attributes->address.low_part);

	/* Unlock Cursor registers. */
	REG_UPDATE(CUR_UPDATE, CURSOR_UPDATE_LOCK, false);
}