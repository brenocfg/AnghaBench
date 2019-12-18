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
struct drm_display_mode {scalar_t__ clock; } ;

/* Variables and functions */
 scalar_t__ KHZ2PICOS (scalar_t__) ; 

__attribute__((used)) static bool drm_mode_match_clock(const struct drm_display_mode *mode1,
				  const struct drm_display_mode *mode2)
{
	/*
	 * do clock check convert to PICOS
	 * so fb modes get matched the same
	 */
	if (mode1->clock && mode2->clock)
		return KHZ2PICOS(mode1->clock) == KHZ2PICOS(mode2->clock);
	else
		return mode1->clock == mode2->clock;
}