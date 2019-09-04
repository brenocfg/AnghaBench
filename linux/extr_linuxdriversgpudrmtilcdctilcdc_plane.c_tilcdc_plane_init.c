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
struct tilcdc_drm_private {int /*<<< orphan*/  num_pixelformats; int /*<<< orphan*/  pixelformats; } ;
struct drm_plane {int dummy; } ;
struct drm_device {int /*<<< orphan*/  dev; struct tilcdc_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  drm_plane_helper_add (struct drm_plane*,int /*<<< orphan*/ *) ; 
 int drm_plane_init (struct drm_device*,struct drm_plane*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  plane_helper_funcs ; 
 int /*<<< orphan*/  tilcdc_plane_funcs ; 

int tilcdc_plane_init(struct drm_device *dev,
		      struct drm_plane *plane)
{
	struct tilcdc_drm_private *priv = dev->dev_private;
	int ret;

	ret = drm_plane_init(dev, plane, 1,
			     &tilcdc_plane_funcs,
			     priv->pixelformats,
			     priv->num_pixelformats,
			     true);
	if (ret) {
		dev_err(dev->dev, "Failed to initialize plane: %d\n", ret);
		return ret;
	}

	drm_plane_helper_add(plane, &plane_helper_funcs);

	return 0;
}