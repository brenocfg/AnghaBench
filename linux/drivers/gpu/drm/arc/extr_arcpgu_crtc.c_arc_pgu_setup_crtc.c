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
struct drm_plane {int dummy; } ;
struct drm_device {struct arcpgu_drm_private* dev_private; } ;
struct arcpgu_drm_private {int /*<<< orphan*/  crtc; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct drm_plane*) ; 
 int PTR_ERR (struct drm_plane*) ; 
 int /*<<< orphan*/  arc_pgu_crtc_funcs ; 
 int /*<<< orphan*/  arc_pgu_crtc_helper_funcs ; 
 int /*<<< orphan*/  arc_pgu_plane_destroy (struct drm_plane*) ; 
 struct drm_plane* arc_pgu_plane_init (struct drm_device*) ; 
 int /*<<< orphan*/  drm_crtc_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int drm_crtc_init_with_planes (struct drm_device*,int /*<<< orphan*/ *,struct drm_plane*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int arc_pgu_setup_crtc(struct drm_device *drm)
{
	struct arcpgu_drm_private *arcpgu = drm->dev_private;
	struct drm_plane *primary;
	int ret;

	primary = arc_pgu_plane_init(drm);
	if (IS_ERR(primary))
		return PTR_ERR(primary);

	ret = drm_crtc_init_with_planes(drm, &arcpgu->crtc, primary, NULL,
					&arc_pgu_crtc_funcs, NULL);
	if (ret) {
		arc_pgu_plane_destroy(primary);
		return ret;
	}

	drm_crtc_helper_add(&arcpgu->crtc, &arc_pgu_crtc_helper_funcs);
	return 0;
}