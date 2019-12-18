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
struct meson_plane {int enabled; struct meson_drm* priv; } ;
struct TYPE_2__ {int osd1_enabled; } ;
struct meson_drm {TYPE_1__ viu; scalar_t__ io_base; } ;
struct drm_plane_state {int dummy; } ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSD1_BLEND_SRC_CTRL ; 
 int /*<<< orphan*/  VIU_OSD1_POSTBLD_SRC_OSD1 ; 
 int /*<<< orphan*/  VPP_MISC ; 
 int /*<<< orphan*/  VPP_OSD1_POSTBLEND ; 
 int /*<<< orphan*/  VPU_COMPATIBLE_G12A ; 
 scalar_t__ _REG (int /*<<< orphan*/ ) ; 
 scalar_t__ meson_vpu_is_compatible (struct meson_drm*,int /*<<< orphan*/ ) ; 
 struct meson_plane* to_meson_plane (struct drm_plane*) ; 
 int /*<<< orphan*/  writel_bits_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void meson_plane_atomic_disable(struct drm_plane *plane,
				       struct drm_plane_state *old_state)
{
	struct meson_plane *meson_plane = to_meson_plane(plane);
	struct meson_drm *priv = meson_plane->priv;

	/* Disable OSD1 */
	if (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A))
		writel_bits_relaxed(VIU_OSD1_POSTBLD_SRC_OSD1, 0,
				    priv->io_base + _REG(OSD1_BLEND_SRC_CTRL));
	else
		writel_bits_relaxed(VPP_OSD1_POSTBLEND, 0,
				    priv->io_base + _REG(VPP_MISC));

	meson_plane->enabled = false;
	priv->viu.osd1_enabled = false;
}