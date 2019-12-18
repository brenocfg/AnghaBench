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
struct vkms_plane_state {struct vkms_composer* composer; } ;
struct vkms_composer {int /*<<< orphan*/  cpp; int /*<<< orphan*/  pitch; int /*<<< orphan*/  offset; int /*<<< orphan*/  fb; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct drm_rect {int dummy; } ;
struct drm_plane_state {int dummy; } ;
struct drm_plane {TYPE_2__* state; } ;
struct drm_framebuffer {TYPE_1__* format; int /*<<< orphan*/ * pitches; int /*<<< orphan*/ * offsets; } ;
struct TYPE_4__ {struct drm_framebuffer dst; struct drm_framebuffer src; int /*<<< orphan*/  crtc; struct drm_framebuffer* fb; } ;
struct TYPE_3__ {int /*<<< orphan*/ * cpp; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_framebuffer_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct drm_framebuffer*,int) ; 
 struct vkms_plane_state* to_vkms_plane_state (TYPE_2__*) ; 

__attribute__((used)) static void vkms_plane_atomic_update(struct drm_plane *plane,
				     struct drm_plane_state *old_state)
{
	struct vkms_plane_state *vkms_plane_state;
	struct drm_framebuffer *fb = plane->state->fb;
	struct vkms_composer *composer;

	if (!plane->state->crtc || !fb)
		return;

	vkms_plane_state = to_vkms_plane_state(plane->state);

	composer = vkms_plane_state->composer;
	memcpy(&composer->src, &plane->state->src, sizeof(struct drm_rect));
	memcpy(&composer->dst, &plane->state->dst, sizeof(struct drm_rect));
	memcpy(&composer->fb, fb, sizeof(struct drm_framebuffer));
	drm_framebuffer_get(&composer->fb);
	composer->offset = fb->offsets[0];
	composer->pitch = fb->pitches[0];
	composer->cpp = fb->format->cpp[0];
}