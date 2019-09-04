#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nv04_crtc_reg {int tv_hskew; int tv_hsync_delay; int tv_hsync_delay2; int tv_vskew; int tv_vsync_delay; int /*<<< orphan*/  tv_vtotal; int /*<<< orphan*/  tv_htotal; } ;
struct nouveau_crtc {size_t index; } ;
struct drm_encoder {int /*<<< orphan*/  crtc; struct drm_device* dev; } ;
struct drm_display_mode {int /*<<< orphan*/  vtotal; int /*<<< orphan*/  htotal; } ;
struct drm_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* mode_set ) (struct drm_encoder*,struct drm_display_mode*,struct drm_display_mode*) ;} ;
struct TYPE_4__ {struct nv04_crtc_reg* crtc_reg; } ;
struct TYPE_5__ {TYPE_1__ mode_reg; } ;

/* Variables and functions */
 TYPE_3__* get_slave_funcs (struct drm_encoder*) ; 
 struct nouveau_crtc* nouveau_crtc (int /*<<< orphan*/ ) ; 
 TYPE_2__* nv04_display (struct drm_device*) ; 
 int /*<<< orphan*/  stub1 (struct drm_encoder*,struct drm_display_mode*,struct drm_display_mode*) ; 

__attribute__((used)) static void nv04_tv_mode_set(struct drm_encoder *encoder,
			     struct drm_display_mode *mode,
			     struct drm_display_mode *adjusted_mode)
{
	struct drm_device *dev = encoder->dev;
	struct nouveau_crtc *nv_crtc = nouveau_crtc(encoder->crtc);
	struct nv04_crtc_reg *regp = &nv04_display(dev)->mode_reg.crtc_reg[nv_crtc->index];

	regp->tv_htotal = adjusted_mode->htotal;
	regp->tv_vtotal = adjusted_mode->vtotal;

	/* These delay the TV signals with respect to the VGA port,
	 * they might be useful if we ever allow a CRTC to drive
	 * multiple outputs.
	 */
	regp->tv_hskew = 1;
	regp->tv_hsync_delay = 1;
	regp->tv_hsync_delay2 = 64;
	regp->tv_vskew = 1;
	regp->tv_vsync_delay = 1;

	get_slave_funcs(encoder)->mode_set(encoder, mode, adjusted_mode);
}