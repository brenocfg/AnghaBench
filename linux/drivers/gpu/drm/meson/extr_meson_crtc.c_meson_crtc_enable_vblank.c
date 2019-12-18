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
struct meson_drm {int dummy; } ;
struct meson_crtc {struct meson_drm* priv; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  meson_venc_enable_vsync (struct meson_drm*) ; 
 struct meson_crtc* to_meson_crtc (struct drm_crtc*) ; 

__attribute__((used)) static int meson_crtc_enable_vblank(struct drm_crtc *crtc)
{
	struct meson_crtc *meson_crtc = to_meson_crtc(crtc);
	struct meson_drm *priv = meson_crtc->priv;

	meson_venc_enable_vsync(priv);

	return 0;
}