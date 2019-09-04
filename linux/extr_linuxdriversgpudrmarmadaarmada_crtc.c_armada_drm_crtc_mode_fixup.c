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
struct drm_display_mode {int flags; } ;
struct drm_crtc {int dummy; } ;
struct armada_crtc {TYPE_1__* variant; } ;
struct TYPE_2__ {int (* compute_clock ) (struct armada_crtc*,struct drm_display_mode*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  has_spu_adv_reg; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_INTERLACE ; 
 struct armada_crtc* drm_to_armada_crtc (struct drm_crtc*) ; 
 int stub1 (struct armada_crtc*,struct drm_display_mode*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool armada_drm_crtc_mode_fixup(struct drm_crtc *crtc,
	const struct drm_display_mode *mode, struct drm_display_mode *adj)
{
	struct armada_crtc *dcrtc = drm_to_armada_crtc(crtc);
	int ret;

	/* We can't do interlaced modes if we don't have the SPU_ADV_REG */
	if (!dcrtc->variant->has_spu_adv_reg &&
	    adj->flags & DRM_MODE_FLAG_INTERLACE)
		return false;

	/* Check whether the display mode is possible */
	ret = dcrtc->variant->compute_clock(dcrtc, adj, NULL);
	if (ret)
		return false;

	return true;
}