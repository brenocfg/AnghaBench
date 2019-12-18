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
struct meson_overlay {struct meson_drm* priv; } ;
struct TYPE_2__ {int vd1_enabled; } ;
struct meson_drm {scalar_t__ io_base; TYPE_1__ viu; } ;
struct drm_plane_state {int dummy; } ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 scalar_t__ VD1_BLEND_SRC_CTRL ; 
 scalar_t__ VD1_IF0_GEN_REG ; 
 scalar_t__ VD2_BLEND_SRC_CTRL ; 
 scalar_t__ VD2_IF0_GEN_REG ; 
 scalar_t__ VPP_MISC ; 
 int VPP_VD1_POSTBLEND ; 
 int VPP_VD1_PREBLEND ; 
 int /*<<< orphan*/  VPU_COMPATIBLE_G12A ; 
 scalar_t__ _REG (scalar_t__) ; 
 scalar_t__ meson_vpu_is_compatible (struct meson_drm*,int /*<<< orphan*/ ) ; 
 struct meson_overlay* to_meson_overlay (struct drm_plane*) ; 
 int /*<<< orphan*/  writel_bits_relaxed (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void meson_overlay_atomic_disable(struct drm_plane *plane,
				       struct drm_plane_state *old_state)
{
	struct meson_overlay *meson_overlay = to_meson_overlay(plane);
	struct meson_drm *priv = meson_overlay->priv;

	DRM_DEBUG_DRIVER("\n");

	priv->viu.vd1_enabled = false;

	/* Disable VD1 */
	if (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A)) {
		writel_relaxed(0, priv->io_base + _REG(VD1_BLEND_SRC_CTRL));
		writel_relaxed(0, priv->io_base + _REG(VD2_BLEND_SRC_CTRL));
		writel_relaxed(0, priv->io_base + _REG(VD1_IF0_GEN_REG + 0x17b0));
		writel_relaxed(0, priv->io_base + _REG(VD2_IF0_GEN_REG + 0x17b0));
	} else
		writel_bits_relaxed(VPP_VD1_POSTBLEND | VPP_VD1_PREBLEND, 0,
				    priv->io_base + _REG(VPP_MISC));

}