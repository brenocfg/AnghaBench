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
struct rcar_du_crtc {int vblank_enable; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIER ; 
 int /*<<< orphan*/  DIER_VBE ; 
 int /*<<< orphan*/  rcar_du_crtc_clr (struct rcar_du_crtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rcar_du_crtc* to_rcar_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void rcar_du_crtc_disable_vblank(struct drm_crtc *crtc)
{
	struct rcar_du_crtc *rcrtc = to_rcar_crtc(crtc);

	rcar_du_crtc_clr(rcrtc, DIER, DIER_VBE);
	rcrtc->vblank_enable = false;
}