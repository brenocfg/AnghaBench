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
struct zx_vou_hw {scalar_t__ osd; } ;
struct zx_plane {struct vou_layer_bits* bits; } ;
struct zx_crtc {struct zx_vou_hw* vou; } ;
struct vou_layer_bits {int /*<<< orphan*/  enable; } ;
struct drm_plane_state {int /*<<< orphan*/  crtc; } ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
 scalar_t__ OSD_CTRL0 ; 
 struct zx_crtc* to_zx_crtc (int /*<<< orphan*/ ) ; 
 struct zx_plane* to_zx_plane (struct drm_plane*) ; 
 int /*<<< orphan*/  zx_writel_mask (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void zx_vou_layer_disable(struct drm_plane *plane,
			  struct drm_plane_state *old_state)
{
	struct zx_crtc *zcrtc = to_zx_crtc(old_state->crtc);
	struct zx_vou_hw *vou = zcrtc->vou;
	struct zx_plane *zplane = to_zx_plane(plane);
	const struct vou_layer_bits *bits = zplane->bits;

	zx_writel_mask(vou->osd + OSD_CTRL0, bits->enable, 0);
}