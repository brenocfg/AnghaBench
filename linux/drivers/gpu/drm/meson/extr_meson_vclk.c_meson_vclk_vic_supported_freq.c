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
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;
struct TYPE_2__ {int pixel_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int,...) ; 
 unsigned int FREQ_1000_1001 (int) ; 
 int MODE_CLOCK_RANGE ; 
 int MODE_OK ; 
 TYPE_1__* params ; 

enum drm_mode_status
meson_vclk_vic_supported_freq(unsigned int freq)
{
	int i;

	DRM_DEBUG_DRIVER("freq = %d\n", freq);

	for (i = 0 ; params[i].pixel_freq ; ++i) {
		DRM_DEBUG_DRIVER("i = %d pixel_freq = %d alt = %d\n",
				 i, params[i].pixel_freq,
				 FREQ_1000_1001(params[i].pixel_freq));
		/* Match strict frequency */
		if (freq == params[i].pixel_freq)
			return MODE_OK;
		/* Match 1000/1001 variant */
		if (freq == FREQ_1000_1001(params[i].pixel_freq))
			return MODE_OK;
	}

	return MODE_CLOCK_RANGE;
}