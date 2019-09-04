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

/* Variables and functions */
 int DRM_MODE_PANEL_ORIENTATION_UNKNOWN ; 

int drm_get_panel_orientation_quirk(int width, int height)
{
	return DRM_MODE_PANEL_ORIENTATION_UNKNOWN;
}