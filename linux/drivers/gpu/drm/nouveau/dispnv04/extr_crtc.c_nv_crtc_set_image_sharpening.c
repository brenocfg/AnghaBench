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
struct nv04_crtc_reg {int ramdac_634; } ;
struct nouveau_crtc {size_t index; int sharpness; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct TYPE_3__ {struct nv04_crtc_reg* crtc_reg; } ;
struct TYPE_4__ {TYPE_1__ mode_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVWriteRAMDAC (struct drm_device*,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NV_PRAMDAC_634 ; 
 struct nouveau_crtc* nouveau_crtc (struct drm_crtc*) ; 
 TYPE_2__* nv04_display (struct drm_device*) ; 

__attribute__((used)) static void nv_crtc_set_image_sharpening(struct drm_crtc *crtc, int level)
{
	struct nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	struct nv04_crtc_reg *regp = &nv04_display(dev)->mode_reg.crtc_reg[nv_crtc->index];

	nv_crtc->sharpness = level;
	if (level < 0)	/* blur is in hw range 0x3f -> 0x20 */
		level += 0x40;
	regp->ramdac_634 = level;
	NVWriteRAMDAC(crtc->dev, nv_crtc->index, NV_PRAMDAC_634, regp->ramdac_634);
}