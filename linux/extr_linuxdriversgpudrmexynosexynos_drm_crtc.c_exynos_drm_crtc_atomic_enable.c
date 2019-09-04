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
struct exynos_drm_crtc {TYPE_1__* ops; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable ) (struct exynos_drm_crtc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  drm_crtc_vblank_on (struct drm_crtc*) ; 
 int /*<<< orphan*/  stub1 (struct exynos_drm_crtc*) ; 
 struct exynos_drm_crtc* to_exynos_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void exynos_drm_crtc_atomic_enable(struct drm_crtc *crtc,
					  struct drm_crtc_state *old_state)
{
	struct exynos_drm_crtc *exynos_crtc = to_exynos_crtc(crtc);

	if (exynos_crtc->ops->enable)
		exynos_crtc->ops->enable(exynos_crtc);

	drm_crtc_vblank_on(crtc);
}