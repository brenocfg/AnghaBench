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
struct vmw_screen_target_display_unit {int /*<<< orphan*/  base; } ;
struct vmw_private {int dummy; } ;
struct vmw_framebuffer {int dummy; } ;
struct drm_plane_state {struct drm_framebuffer* fb; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {int /*<<< orphan*/  dev; TYPE_1__* primary; } ;
struct TYPE_2__ {struct drm_plane_state* state; } ;

/* Variables and functions */
 struct vmw_screen_target_display_unit* vmw_crtc_to_stdu (struct drm_crtc*) ; 
 struct vmw_framebuffer* vmw_framebuffer_to_vfb (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  vmw_kms_add_active (struct vmw_private*,int /*<<< orphan*/ *,struct vmw_framebuffer*) ; 
 int /*<<< orphan*/  vmw_kms_del_active (struct vmw_private*,int /*<<< orphan*/ *) ; 
 struct vmw_private* vmw_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmw_stdu_crtc_atomic_enable(struct drm_crtc *crtc,
					struct drm_crtc_state *old_state)
{
	struct drm_plane_state *plane_state = crtc->primary->state;
	struct vmw_private *dev_priv;
	struct vmw_screen_target_display_unit *stdu;
	struct vmw_framebuffer *vfb;
	struct drm_framebuffer *fb;


	stdu     = vmw_crtc_to_stdu(crtc);
	dev_priv = vmw_priv(crtc->dev);
	fb       = plane_state->fb;

	vfb = (fb) ? vmw_framebuffer_to_vfb(fb) : NULL;

	if (vfb)
		vmw_kms_add_active(dev_priv, &stdu->base, vfb);
	else
		vmw_kms_del_active(dev_priv, &stdu->base);
}