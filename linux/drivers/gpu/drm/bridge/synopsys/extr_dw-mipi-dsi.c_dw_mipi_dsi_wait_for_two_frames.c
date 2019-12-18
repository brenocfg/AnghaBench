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
struct drm_display_mode {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MSEC_PER_SEC ; 
 int drm_mode_vrefresh (struct drm_display_mode const*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void dw_mipi_dsi_wait_for_two_frames(const struct drm_display_mode *mode)
{
	int refresh, two_frames;

	refresh = drm_mode_vrefresh(mode);
	two_frames = DIV_ROUND_UP(MSEC_PER_SEC, refresh) * 2;
	msleep(two_frames);
}