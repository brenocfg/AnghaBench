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
struct meson_plane {struct meson_drm* priv; } ;
struct meson_drm {scalar_t__ io_base; } ;
struct drm_plane_state {int dummy; } ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VPP_MISC ; 
 int /*<<< orphan*/  VPP_OSD1_POSTBLEND ; 
 scalar_t__ _REG (int /*<<< orphan*/ ) ; 
 struct meson_plane* to_meson_plane (struct drm_plane*) ; 
 int /*<<< orphan*/  writel_bits_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void meson_plane_atomic_disable(struct drm_plane *plane,
				       struct drm_plane_state *old_state)
{
	struct meson_plane *meson_plane = to_meson_plane(plane);
	struct meson_drm *priv = meson_plane->priv;

	/* Disable OSD1 */
	writel_bits_relaxed(VPP_OSD1_POSTBLEND, 0,
			    priv->io_base + _REG(VPP_MISC));

}