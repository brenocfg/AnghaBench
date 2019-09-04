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
struct tg_color {int /*<<< orphan*/  color_r_cr; int /*<<< orphan*/  color_g_y; int /*<<< orphan*/  color_b_cb; } ;
struct dce110_timing_generator {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC0_CRTC_OVERSCAN_COLOR ; 
 int /*<<< orphan*/  CRTC_OVERSCAN_COLOR_BLUE ; 
 int /*<<< orphan*/  CRTC_OVERSCAN_COLOR_GREEN ; 
 int /*<<< orphan*/  CRTC_OVERSCAN_COLOR_RED ; 
 int /*<<< orphan*/  CRTC_REG_SET_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dce110_timing_generator* DCE110TG_FROM_TG (struct timing_generator*) ; 

void dce120_tg_set_overscan_color(struct timing_generator *tg,
	const struct tg_color *overscan_color)
{
	struct dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	CRTC_REG_SET_3(
		CRTC0_CRTC_OVERSCAN_COLOR,
		CRTC_OVERSCAN_COLOR_BLUE, overscan_color->color_b_cb,
		CRTC_OVERSCAN_COLOR_GREEN, overscan_color->color_g_y,
		CRTC_OVERSCAN_COLOR_RED, overscan_color->color_r_cr);
}