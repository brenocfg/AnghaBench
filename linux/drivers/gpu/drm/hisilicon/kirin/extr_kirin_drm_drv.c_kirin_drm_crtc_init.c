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
struct kirin_drm_data {int /*<<< orphan*/  crtc_helper_funcs; int /*<<< orphan*/  crtc_funcs; } ;
struct drm_plane {int dummy; } ;
struct drm_device {TYPE_1__* dev; } ;
struct drm_crtc {struct device_node* port; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  drm_crtc_helper_add (struct drm_crtc*,int /*<<< orphan*/ ) ; 
 int drm_crtc_init_with_planes (struct drm_device*,struct drm_crtc*,struct drm_plane*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct device_node* of_get_child_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static int kirin_drm_crtc_init(struct drm_device *dev, struct drm_crtc *crtc,
			       struct drm_plane *plane,
			       const struct kirin_drm_data *driver_data)
{
	struct device_node *port;
	int ret;

	/* set crtc port so that
	 * drm_of_find_possible_crtcs call works
	 */
	port = of_get_child_by_name(dev->dev->of_node, "port");
	if (!port) {
		DRM_ERROR("no port node found in %pOF\n", dev->dev->of_node);
		return -EINVAL;
	}
	of_node_put(port);
	crtc->port = port;

	ret = drm_crtc_init_with_planes(dev, crtc, plane, NULL,
					driver_data->crtc_funcs, NULL);
	if (ret) {
		DRM_ERROR("failed to init crtc.\n");
		return ret;
	}

	drm_crtc_helper_add(crtc, driver_data->crtc_helper_funcs);

	return 0;
}