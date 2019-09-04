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
struct mtk_drm_crtc {int /*<<< orphan*/  base; } ;
struct drm_plane {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_crtc_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int drm_crtc_init_with_planes (struct drm_device*,int /*<<< orphan*/ *,struct drm_plane*,struct drm_plane*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_crtc_funcs ; 
 int /*<<< orphan*/  mtk_crtc_helper_funcs ; 

__attribute__((used)) static int mtk_drm_crtc_init(struct drm_device *drm,
			     struct mtk_drm_crtc *mtk_crtc,
			     struct drm_plane *primary,
			     struct drm_plane *cursor, unsigned int pipe)
{
	int ret;

	ret = drm_crtc_init_with_planes(drm, &mtk_crtc->base, primary, cursor,
					&mtk_crtc_funcs, NULL);
	if (ret)
		goto err_cleanup_crtc;

	drm_crtc_helper_add(&mtk_crtc->base, &mtk_crtc_helper_funcs);

	return 0;

err_cleanup_crtc:
	drm_crtc_cleanup(&mtk_crtc->base);
	return ret;
}