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
struct msm_kms {int /*<<< orphan*/  aspace; } ;
struct mdp4_plane {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {struct msm_kms base; } ;
struct mdp4_kms {TYPE_1__ base; } ;
struct drm_plane_state {struct drm_framebuffer* fb; } ;
struct drm_plane {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct drm_framebuffer {TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mdp4_kms* get_kms (struct drm_plane*) ; 
 int /*<<< orphan*/  msm_framebuffer_cleanup (struct drm_framebuffer*,int /*<<< orphan*/ ) ; 
 struct mdp4_plane* to_mdp4_plane (struct drm_plane*) ; 

__attribute__((used)) static void mdp4_plane_cleanup_fb(struct drm_plane *plane,
				  struct drm_plane_state *old_state)
{
	struct mdp4_plane *mdp4_plane = to_mdp4_plane(plane);
	struct mdp4_kms *mdp4_kms = get_kms(plane);
	struct msm_kms *kms = &mdp4_kms->base.base;
	struct drm_framebuffer *fb = old_state->fb;

	if (!fb)
		return;

	DBG("%s: cleanup: FB[%u]", mdp4_plane->name, fb->base.id);
	msm_framebuffer_cleanup(fb, kms->aspace);
}