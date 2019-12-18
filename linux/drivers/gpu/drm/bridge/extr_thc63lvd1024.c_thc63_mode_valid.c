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
struct TYPE_2__ {scalar_t__ dual_link; } ;
struct thc63_dev {TYPE_1__ timings; } ;
struct drm_display_mode {unsigned int clock; } ;
struct drm_bridge {int dummy; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;

/* Variables and functions */
 int MODE_CLOCK_HIGH ; 
 int MODE_CLOCK_LOW ; 
 int MODE_OK ; 
 struct thc63_dev* to_thc63 (struct drm_bridge*) ; 

__attribute__((used)) static enum drm_mode_status thc63_mode_valid(struct drm_bridge *bridge,
					const struct drm_display_mode *mode)
{
	struct thc63_dev *thc63 = to_thc63(bridge);
	unsigned int min_freq;
	unsigned int max_freq;

	/*
	 * The THC63LVD1024 pixel rate range is 8 to 135 MHz in all modes but
	 * dual-in, single-out where it is 40 to 150 MHz. As dual-in, dual-out
	 * isn't supported by the driver yet, simply derive the limits from the
	 * input mode.
	 */
	if (thc63->timings.dual_link) {
		min_freq = 40000;
		max_freq = 150000;
	} else {
		min_freq = 8000;
		max_freq = 135000;
	}

	if (mode->clock < min_freq)
		return MODE_CLOCK_LOW;

	if (mode->clock > max_freq)
		return MODE_CLOCK_HIGH;

	return MODE_OK;
}