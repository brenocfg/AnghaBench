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
struct sti_vtg {int dummy; } ;
struct sti_private {struct sti_compositor* compo; } ;
struct sti_compositor {struct sti_vtg** vtg; TYPE_1__** mixer; struct notifier_block* vtg_vblank_nb; } ;
struct notifier_block {int dummy; } ;
struct drm_device {struct sti_private* dev_private; } ;
struct drm_crtc {int dummy; } ;
struct TYPE_2__ {struct drm_crtc drm_crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 scalar_t__ sti_vtg_register_client (struct sti_vtg*,struct notifier_block*,struct drm_crtc*) ; 

int sti_crtc_enable_vblank(struct drm_device *dev, unsigned int pipe)
{
	struct sti_private *dev_priv = dev->dev_private;
	struct sti_compositor *compo = dev_priv->compo;
	struct notifier_block *vtg_vblank_nb = &compo->vtg_vblank_nb[pipe];
	struct drm_crtc *crtc = &compo->mixer[pipe]->drm_crtc;
	struct sti_vtg *vtg = compo->vtg[pipe];

	DRM_DEBUG_DRIVER("\n");

	if (sti_vtg_register_client(vtg, vtg_vblank_nb, crtc)) {
		DRM_ERROR("Cannot register VTG notifier\n");
		return -EINVAL;
	}

	return 0;
}