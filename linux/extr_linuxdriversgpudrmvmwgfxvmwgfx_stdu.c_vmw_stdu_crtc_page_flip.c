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
typedef  int /*<<< orphan*/  uint32_t ;
struct vmw_screen_target_display_unit {int /*<<< orphan*/  defined; } ;
struct vmw_private {int dummy; } ;
struct drm_pending_vblank_event {int dummy; } ;
struct drm_modeset_acquire_ctx {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_crtc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EINVAL ; 
 int drm_atomic_helper_page_flip (struct drm_crtc*,struct drm_framebuffer*,struct drm_pending_vblank_event*,int /*<<< orphan*/ ,struct drm_modeset_acquire_ctx*) ; 
 struct vmw_screen_target_display_unit* vmw_crtc_to_stdu (struct drm_crtc*) ; 
 int /*<<< orphan*/  vmw_kms_crtc_flippable (struct vmw_private*,struct drm_crtc*) ; 
 struct vmw_private* vmw_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vmw_stdu_crtc_page_flip(struct drm_crtc *crtc,
				   struct drm_framebuffer *new_fb,
				   struct drm_pending_vblank_event *event,
				   uint32_t flags,
				   struct drm_modeset_acquire_ctx *ctx)

{
	struct vmw_private *dev_priv = vmw_priv(crtc->dev);
	struct vmw_screen_target_display_unit *stdu = vmw_crtc_to_stdu(crtc);
	int ret;

	if (!stdu->defined || !vmw_kms_crtc_flippable(dev_priv, crtc))
		return -EINVAL;

	ret = drm_atomic_helper_page_flip(crtc, new_fb, event, flags, ctx);
	if (ret) {
		DRM_ERROR("Page flip error %d.\n", ret);
		return ret;
	}

	return 0;
}