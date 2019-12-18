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
struct TYPE_4__ {TYPE_1__* dev; } ;
struct drm_simple_display_pipe {TYPE_2__ crtc; } ;
struct drm_plane_state {int dummy; } ;
struct drm_crtc_state {int /*<<< orphan*/  mode; } ;
struct bochs_device {int dummy; } ;
struct TYPE_3__ {struct bochs_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  bochs_hw_setmode (struct bochs_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bochs_plane_update (struct bochs_device*,struct drm_plane_state*) ; 

__attribute__((used)) static void bochs_pipe_enable(struct drm_simple_display_pipe *pipe,
			      struct drm_crtc_state *crtc_state,
			      struct drm_plane_state *plane_state)
{
	struct bochs_device *bochs = pipe->crtc.dev->dev_private;

	bochs_hw_setmode(bochs, &crtc_state->mode);
	bochs_plane_update(bochs, plane_state);
}