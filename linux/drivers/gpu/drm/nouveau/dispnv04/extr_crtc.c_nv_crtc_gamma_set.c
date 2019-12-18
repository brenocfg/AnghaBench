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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_6__ {scalar_t__ depth; } ;
struct TYPE_5__ {TYPE_1__* primary; } ;
struct nouveau_crtc {TYPE_3__ lut; TYPE_2__ base; } ;
struct drm_modeset_acquire_ctx {int dummy; } ;
struct drm_crtc {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  fb; } ;

/* Variables and functions */
 struct nouveau_crtc* nouveau_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  nv_crtc_gamma_load (struct drm_crtc*) ; 

__attribute__((used)) static int
nv_crtc_gamma_set(struct drm_crtc *crtc, u16 *r, u16 *g, u16 *b,
		  uint32_t size,
		  struct drm_modeset_acquire_ctx *ctx)
{
	struct nouveau_crtc *nv_crtc = nouveau_crtc(crtc);

	/* We need to know the depth before we upload, but it's possible to
	 * get called before a framebuffer is bound.  If this is the case,
	 * mark the lut values as dirty by setting depth==0, and it'll be
	 * uploaded on the first mode_set_base()
	 */
	if (!nv_crtc->base.primary->fb) {
		nv_crtc->lut.depth = 0;
		return 0;
	}

	nv_crtc_gamma_load(crtc);

	return 0;
}