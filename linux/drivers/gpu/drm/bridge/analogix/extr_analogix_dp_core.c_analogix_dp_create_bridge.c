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
struct drm_device {int /*<<< orphan*/  dev; } ;
struct drm_bridge {int /*<<< orphan*/ * funcs; struct analogix_dp_device* driver_private; } ;
struct analogix_dp_device {int /*<<< orphan*/  encoder; struct drm_bridge* bridge; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  analogix_dp_bridge_funcs ; 
 struct drm_bridge* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int drm_bridge_attach (int /*<<< orphan*/ ,struct drm_bridge*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int analogix_dp_create_bridge(struct drm_device *drm_dev,
				     struct analogix_dp_device *dp)
{
	struct drm_bridge *bridge;
	int ret;

	bridge = devm_kzalloc(drm_dev->dev, sizeof(*bridge), GFP_KERNEL);
	if (!bridge) {
		DRM_ERROR("failed to allocate for drm bridge\n");
		return -ENOMEM;
	}

	dp->bridge = bridge;

	bridge->driver_private = dp;
	bridge->funcs = &analogix_dp_bridge_funcs;

	ret = drm_bridge_attach(dp->encoder, bridge, NULL);
	if (ret) {
		DRM_ERROR("failed to attach drm bridge\n");
		return -EINVAL;
	}

	return 0;
}