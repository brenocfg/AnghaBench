#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct timing_generator {int /*<<< orphan*/  ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  crtc; } ;
struct dce110_timing_generator {TYPE_1__ offsets; } ;
typedef  enum trigger_source_select { ____Placeholder_trigger_source_select } trigger_source_select ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC0_CRTC_FORCE_COUNT_NOW_CNTL ; 
 int /*<<< orphan*/  CRTC0_CRTC_TRIGB_CNTL ; 
 int /*<<< orphan*/  CRTC0_CRTC_TRIGB_CNTL__CRTC_TRIGB_CLEAR ; 
 int /*<<< orphan*/  CRTC0_CRTC_TRIGB_CNTL__CRTC_TRIGB_DELAY ; 
 int /*<<< orphan*/  CRTC0_CRTC_TRIGB_CNTL__CRTC_TRIGB_FALLING_EDGE_DETECT_CNTL ; 
 int /*<<< orphan*/  CRTC0_CRTC_TRIGB_CNTL__CRTC_TRIGB_FREQUENCY_SELECT ; 
 int /*<<< orphan*/  CRTC0_CRTC_TRIGB_CNTL__CRTC_TRIGB_POLARITY_SELECT ; 
 int /*<<< orphan*/  CRTC0_CRTC_TRIGB_CNTL__CRTC_TRIGB_RISING_EDGE_DETECT_CNTL ; 
 int /*<<< orphan*/  CRTC0_CRTC_TRIGB_CNTL__CRTC_TRIGB_SOURCE_SELECT ; 
 int /*<<< orphan*/  CRTC0_CRTC_V_SYNC_A_CNTL ; 
 int /*<<< orphan*/  CRTC_FORCE_COUNT_NOW_CLEAR ; 
 int /*<<< orphan*/  CRTC_FORCE_COUNT_NOW_MODE ; 
 int /*<<< orphan*/  CRTC_FORCE_COUNT_NOW_TRIG_SEL ; 
 int /*<<< orphan*/  CRTC_REG_UPDATE_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CRTC_REG_UPDATE_N (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CRTC_V_SYNC_A_POL ; 
 struct dce110_timing_generator* DCE110TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  FD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRIGGER_POLARITY_SELECT_LOGIC_ZERO ; 
 int TRIGGER_SOURCE_SELECT_GSL_GROUP0 ; 
 int TRIGGER_SOURCE_SELECT_LOGIC_ZERO ; 
 int dm_read_reg_soc15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_reg_field_value (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCRTC0_CRTC_V_SYNC_A_CNTL ; 

void dce120_timing_generator_enable_reset_trigger(
	struct timing_generator *tg,
	int source)
{
	enum trigger_source_select trig_src_select = TRIGGER_SOURCE_SELECT_LOGIC_ZERO;
	struct dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uint32_t rising_edge = 0;
	uint32_t falling_edge = 0;
	/* Setup trigger edge */
	uint32_t pol_value = dm_read_reg_soc15(
									tg->ctx,
									mmCRTC0_CRTC_V_SYNC_A_CNTL,
									tg110->offsets.crtc);

	/* Register spec has reversed definition:
	 *	0 for positive, 1 for negative */
	if (get_reg_field_value(pol_value,
			CRTC0_CRTC_V_SYNC_A_CNTL,
			CRTC_V_SYNC_A_POL) == 0) {
		rising_edge = 1;
	} else {
		falling_edge = 1;
	}

	/* TODO What about other sources ?*/
	trig_src_select = TRIGGER_SOURCE_SELECT_GSL_GROUP0;

	CRTC_REG_UPDATE_N(CRTC0_CRTC_TRIGB_CNTL, 7,
		FD(CRTC0_CRTC_TRIGB_CNTL__CRTC_TRIGB_SOURCE_SELECT), trig_src_select,
		FD(CRTC0_CRTC_TRIGB_CNTL__CRTC_TRIGB_POLARITY_SELECT), TRIGGER_POLARITY_SELECT_LOGIC_ZERO,
		FD(CRTC0_CRTC_TRIGB_CNTL__CRTC_TRIGB_RISING_EDGE_DETECT_CNTL), rising_edge,
		FD(CRTC0_CRTC_TRIGB_CNTL__CRTC_TRIGB_FALLING_EDGE_DETECT_CNTL), falling_edge,
		/* send every signal */
		FD(CRTC0_CRTC_TRIGB_CNTL__CRTC_TRIGB_FREQUENCY_SELECT), 0,
		/* no delay */
		FD(CRTC0_CRTC_TRIGB_CNTL__CRTC_TRIGB_DELAY), 0,
		/* clear trigger status */
		FD(CRTC0_CRTC_TRIGB_CNTL__CRTC_TRIGB_CLEAR), 1);

	CRTC_REG_UPDATE_3(
			CRTC0_CRTC_FORCE_COUNT_NOW_CNTL,
			CRTC_FORCE_COUNT_NOW_MODE, 2,
			CRTC_FORCE_COUNT_NOW_TRIG_SEL, 1,
			CRTC_FORCE_COUNT_NOW_CLEAR, 1);
}