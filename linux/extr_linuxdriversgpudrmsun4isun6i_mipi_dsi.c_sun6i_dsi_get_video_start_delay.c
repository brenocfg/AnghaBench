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
typedef  scalar_t__ u16 ;
struct sun6i_dsi {int dummy; } ;
struct drm_display_mode {scalar_t__ vdisplay; scalar_t__ vsync_end; scalar_t__ vtotal; } ;

/* Variables and functions */

__attribute__((used)) static u16 sun6i_dsi_get_video_start_delay(struct sun6i_dsi *dsi,
					   struct drm_display_mode *mode)
{
	return mode->vtotal - (mode->vsync_end - mode->vdisplay) + 1;
}