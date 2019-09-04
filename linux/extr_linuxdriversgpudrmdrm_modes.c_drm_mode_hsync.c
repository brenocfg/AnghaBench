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
struct drm_display_mode {int hsync; int htotal; int clock; } ;

/* Variables and functions */

int drm_mode_hsync(const struct drm_display_mode *mode)
{
	unsigned int calc_val;

	if (mode->hsync)
		return mode->hsync;

	if (mode->htotal <= 0)
		return 0;

	calc_val = (mode->clock * 1000) / mode->htotal; /* hsync in Hz */
	calc_val += 500;				/* round to 1000Hz */
	calc_val /= 1000;				/* truncate to kHz */

	return calc_val;
}