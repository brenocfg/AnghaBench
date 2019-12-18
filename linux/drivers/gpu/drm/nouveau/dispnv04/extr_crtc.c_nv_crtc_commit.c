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
typedef  int /*<<< orphan*/  uint8_t ;
struct nouveau_crtc {int /*<<< orphan*/  index; } ;
struct drm_device {int dummy; } ;
struct drm_crtc_helper_funcs {int /*<<< orphan*/  (* dpms ) (struct drm_crtc*,int /*<<< orphan*/ ) ;} ;
struct drm_crtc {int /*<<< orphan*/  y; int /*<<< orphan*/  x; struct drm_crtc_helper_funcs* helper_private; struct drm_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  mode_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_DPMS_ON ; 
 int /*<<< orphan*/  MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVReadVgaCrtc (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVWriteVgaCrtc (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NV_CIO_CRE_RCR ; 
 int /*<<< orphan*/  NV_CIO_CRE_RCR_ENDIAN_BIG ; 
 int /*<<< orphan*/  drm_crtc_vblank_on (struct drm_crtc*) ; 
 struct nouveau_crtc* nouveau_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  nouveau_hw_load_state (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nv04_crtc_mode_set_base (struct drm_crtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* nv04_display (struct drm_device*) ; 
 int /*<<< orphan*/  stub1 (struct drm_crtc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nv_crtc_commit(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	const struct drm_crtc_helper_funcs *funcs = crtc->helper_private;
	struct nouveau_crtc *nv_crtc = nouveau_crtc(crtc);

	nouveau_hw_load_state(dev, nv_crtc->index, &nv04_display(dev)->mode_reg);
	nv04_crtc_mode_set_base(crtc, crtc->x, crtc->y, NULL);

#ifdef __BIG_ENDIAN
	/* turn on LFB swapping */
	{
		uint8_t tmp = NVReadVgaCrtc(dev, nv_crtc->index, NV_CIO_CRE_RCR);
		tmp |= MASK(NV_CIO_CRE_RCR_ENDIAN_BIG);
		NVWriteVgaCrtc(dev, nv_crtc->index, NV_CIO_CRE_RCR, tmp);
	}
#endif

	funcs->dpms(crtc, DRM_MODE_DPMS_ON);
	drm_crtc_vblank_on(crtc);
}