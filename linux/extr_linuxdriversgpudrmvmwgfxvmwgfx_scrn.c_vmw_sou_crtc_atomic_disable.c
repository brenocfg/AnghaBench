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
struct vmw_screen_object_unit {scalar_t__ defined; } ;
struct vmw_private {int dummy; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 struct vmw_screen_object_unit* vmw_crtc_to_sou (struct drm_crtc*) ; 
 struct vmw_private* vmw_priv (int /*<<< orphan*/ ) ; 
 int vmw_sou_fifo_destroy (struct vmw_private*,struct vmw_screen_object_unit*) ; 

__attribute__((used)) static void vmw_sou_crtc_atomic_disable(struct drm_crtc *crtc,
					struct drm_crtc_state *old_state)
{
	struct vmw_private *dev_priv;
	struct vmw_screen_object_unit *sou;
	int ret;


	if (!crtc) {
		DRM_ERROR("CRTC is NULL\n");
		return;
	}

	sou = vmw_crtc_to_sou(crtc);
	dev_priv = vmw_priv(crtc->dev);

	if (sou->defined) {
		ret = vmw_sou_fifo_destroy(dev_priv, sou);
		if (ret)
			DRM_ERROR("Failed to destroy Screen Object\n");
	}
}