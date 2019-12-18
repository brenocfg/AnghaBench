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
struct rcar_du_vsp_plane {unsigned int index; int /*<<< orphan*/  plane; struct rcar_du_vsp* vsp; } ;
struct rcar_du_vsp {int num_planes; struct rcar_du_vsp_plane* planes; int /*<<< orphan*/ * vsp; struct rcar_du_device* dev; } ;
struct rcar_du_device {int /*<<< orphan*/  ddev; int /*<<< orphan*/  dev; TYPE_1__* info; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;
typedef  enum drm_plane_type { ____Placeholder_drm_plane_type } drm_plane_type ;
struct TYPE_2__ {int gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int DRM_PLANE_TYPE_OVERLAY ; 
 int DRM_PLANE_TYPE_PRIMARY ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct rcar_du_vsp_plane* devm_kcalloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_plane_create_alpha_property (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_plane_create_zpos_property (int /*<<< orphan*/ *,int,int,unsigned int) ; 
 int /*<<< orphan*/  drm_plane_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int drm_universal_plane_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 unsigned int hweight32 (unsigned int) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 int /*<<< orphan*/  rcar_du_vsp_formats ; 
 int /*<<< orphan*/  rcar_du_vsp_plane_funcs ; 
 int /*<<< orphan*/  rcar_du_vsp_plane_helper_funcs ; 
 int vsp1_du_init (int /*<<< orphan*/ *) ; 

int rcar_du_vsp_init(struct rcar_du_vsp *vsp, struct device_node *np,
		     unsigned int crtcs)
{
	struct rcar_du_device *rcdu = vsp->dev;
	struct platform_device *pdev;
	unsigned int num_crtcs = hweight32(crtcs);
	unsigned int i;
	int ret;

	/* Find the VSP device and initialize it. */
	pdev = of_find_device_by_node(np);
	if (!pdev)
		return -ENXIO;

	vsp->vsp = &pdev->dev;

	ret = vsp1_du_init(vsp->vsp);
	if (ret < 0)
		return ret;

	 /*
	  * The VSP2D (Gen3) has 5 RPFs, but the VSP1D (Gen2) is limited to
	  * 4 RPFs.
	  */
	vsp->num_planes = rcdu->info->gen >= 3 ? 5 : 4;

	vsp->planes = devm_kcalloc(rcdu->dev, vsp->num_planes,
				   sizeof(*vsp->planes), GFP_KERNEL);
	if (!vsp->planes)
		return -ENOMEM;

	for (i = 0; i < vsp->num_planes; ++i) {
		enum drm_plane_type type = i < num_crtcs
					 ? DRM_PLANE_TYPE_PRIMARY
					 : DRM_PLANE_TYPE_OVERLAY;
		struct rcar_du_vsp_plane *plane = &vsp->planes[i];

		plane->vsp = vsp;
		plane->index = i;

		ret = drm_universal_plane_init(rcdu->ddev, &plane->plane, crtcs,
					       &rcar_du_vsp_plane_funcs,
					       rcar_du_vsp_formats,
					       ARRAY_SIZE(rcar_du_vsp_formats),
					       NULL, type, NULL);
		if (ret < 0)
			return ret;

		drm_plane_helper_add(&plane->plane,
				     &rcar_du_vsp_plane_helper_funcs);

		if (type == DRM_PLANE_TYPE_PRIMARY)
			continue;

		drm_plane_create_alpha_property(&plane->plane);
		drm_plane_create_zpos_property(&plane->plane, 1, 1,
					       vsp->num_planes - 1);
	}

	return 0;
}