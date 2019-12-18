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
 int /*<<< orphan*/  CRTC0_CRTC_STATIC_SCREEN_CONTROL ; 
 int /*<<< orphan*/  CRTC_REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CRTC_STATIC_SCREEN_EVENT_MASK ; 
 int /*<<< orphan*/  CRTC_STATIC_SCREEN_FRAME_COUNT ; 
 struct dce110_timing_generator* DCE110TG_FROM_TG (struct timing_generator*) ; 

__attribute__((used)) static void dce120_timing_generator_set_static_screen_control(
	struct timing_generator *tg,
	uint32_t value)
{
	struct dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	CRTC_REG_UPDATE_2(CRTC0_CRTC_STATIC_SCREEN_CONTROL,
			CRTC_STATIC_SCREEN_EVENT_MASK, value,
			CRTC_STATIC_SCREEN_FRAME_COUNT, 2);
}