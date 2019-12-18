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
struct timing_generator {int dummy; } ;
struct dce110_timing_generator {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC0_CRTC_FORCE_COUNT_NOW_CNTL ; 
 int /*<<< orphan*/  CRTC0_CRTC_TRIGB_CNTL ; 
 int /*<<< orphan*/  CRTC_FORCE_COUNT_NOW_CLEAR ; 
 int /*<<< orphan*/  CRTC_FORCE_COUNT_NOW_MODE ; 
 int /*<<< orphan*/  CRTC_REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CRTC_REG_UPDATE_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CRTC_TRIGB_CLEAR ; 
 int /*<<< orphan*/  CRTC_TRIGB_POLARITY_SELECT ; 
 int /*<<< orphan*/  CRTC_TRIGB_SOURCE_SELECT ; 
 struct dce110_timing_generator* DCE110TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  TRIGGER_POLARITY_SELECT_LOGIC_ZERO ; 
 int /*<<< orphan*/  TRIGGER_SOURCE_SELECT_LOGIC_ZERO ; 

void dce120_timing_generator_disable_reset_trigger(
	struct timing_generator *tg)
{
	struct dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	CRTC_REG_UPDATE_2(
		CRTC0_CRTC_FORCE_COUNT_NOW_CNTL,
		CRTC_FORCE_COUNT_NOW_MODE, 0,
		CRTC_FORCE_COUNT_NOW_CLEAR, 1);

	CRTC_REG_UPDATE_3(
		CRTC0_CRTC_TRIGB_CNTL,
		CRTC_TRIGB_SOURCE_SELECT, TRIGGER_SOURCE_SELECT_LOGIC_ZERO,
		CRTC_TRIGB_POLARITY_SELECT, TRIGGER_POLARITY_SELECT_LOGIC_ZERO,
		/* clear trigger status */
		CRTC_TRIGB_CLEAR, 1);

}