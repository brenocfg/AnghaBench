#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
struct timing_generator {int dummy; } ;
struct optc {int dummy; } ;

/* Variables and functions */
 struct optc* DCN10TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  OTG_STATIC_SCREEN_CONTROL ; 
 int /*<<< orphan*/  OTG_STATIC_SCREEN_EVENT_MASK ; 
 int /*<<< orphan*/  OTG_STATIC_SCREEN_FRAME_COUNT ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int STATIC_SCREEN_EVENT_MASK_RANGETIMING_DOUBLE_BUFFER_UPDATE_EN ; 

void optc1_set_static_screen_control(
	struct timing_generator *optc,
	uint32_t value)
{
	struct optc *optc1 = DCN10TG_FROM_TG(optc);

	/* Bit 8 is no longer applicable in RV for PSR case,
	 * set bit 8 to 0 if given
	 */
	if ((value & STATIC_SCREEN_EVENT_MASK_RANGETIMING_DOUBLE_BUFFER_UPDATE_EN)
			!= 0)
		value = value &
		~STATIC_SCREEN_EVENT_MASK_RANGETIMING_DOUBLE_BUFFER_UPDATE_EN;

	REG_SET_2(OTG_STATIC_SCREEN_CONTROL, 0,
			OTG_STATIC_SCREEN_EVENT_MASK, value,
			OTG_STATIC_SCREEN_FRAME_COUNT, 2);
}