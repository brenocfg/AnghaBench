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
typedef  int /*<<< orphan*/  uint32_t ;
struct timing_generator {int dummy; } ;
struct dce110_timing_generator {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC0_CRTC_CONTROL ; 
 int /*<<< orphan*/  CRTC_HBLANK_EARLY_CONTROL ; 
 int /*<<< orphan*/  CRTC_REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dce110_timing_generator* DCE110TG_FROM_TG (struct timing_generator*) ; 

void dce120_timing_generator_set_early_control(
		struct timing_generator *tg,
		uint32_t early_cntl)
{
	struct dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	CRTC_REG_UPDATE(CRTC0_CRTC_CONTROL,
			CRTC_HBLANK_EARLY_CONTROL, early_cntl);
}