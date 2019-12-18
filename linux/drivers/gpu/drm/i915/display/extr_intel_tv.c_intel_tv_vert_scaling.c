#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_display_mode {int crtc_vdisplay; } ;
struct TYPE_3__ {int top; int bottom; } ;
struct TYPE_4__ {TYPE_1__ margins; } ;
struct drm_connector_state {TYPE_2__ tv; } ;

/* Variables and functions */

__attribute__((used)) static bool intel_tv_vert_scaling(const struct drm_display_mode *tv_mode,
				  const struct drm_connector_state *conn_state,
				  int vdisplay)
{
	return tv_mode->crtc_vdisplay -
		conn_state->tv.margins.top -
		conn_state->tv.margins.bottom !=
		vdisplay;
}