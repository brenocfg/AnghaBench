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
struct drm_plane_state {int /*<<< orphan*/  fb; } ;
struct drm_crtc_state {int /*<<< orphan*/  mode; } ;
struct cirrus_device {int dummy; } ;
struct TYPE_3__ {struct cirrus_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  cirrus_fb_blit_fullscreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cirrus_mode_set (struct cirrus_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cirrus_pipe_enable(struct drm_simple_display_pipe *pipe,
			       struct drm_crtc_state *crtc_state,
			       struct drm_plane_state *plane_state)
{
	struct cirrus_device *cirrus = pipe->crtc.dev->dev_private;

	cirrus_mode_set(cirrus, &crtc_state->mode, plane_state->fb);
	cirrus_fb_blit_fullscreen(plane_state->fb);
}