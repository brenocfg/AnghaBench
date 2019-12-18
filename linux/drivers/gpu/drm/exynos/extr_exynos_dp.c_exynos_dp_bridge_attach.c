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
struct exynos_dp_device {int /*<<< orphan*/  dev; scalar_t__ ptn_bridge; int /*<<< orphan*/  encoder; struct drm_connector* connector; } ;
struct drm_connector {int dummy; } ;
struct drm_bridge {int /*<<< orphan*/ * next; } ;
struct analogix_dp_plat_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 int drm_bridge_attach (int /*<<< orphan*/ *,scalar_t__,struct drm_bridge*) ; 
 struct exynos_dp_device* to_dp (struct analogix_dp_plat_data*) ; 

__attribute__((used)) static int exynos_dp_bridge_attach(struct analogix_dp_plat_data *plat_data,
				   struct drm_bridge *bridge,
				   struct drm_connector *connector)
{
	struct exynos_dp_device *dp = to_dp(plat_data);
	int ret;

	dp->connector = connector;

	/* Pre-empt DP connector creation if there's a bridge */
	if (dp->ptn_bridge) {
		ret = drm_bridge_attach(&dp->encoder, dp->ptn_bridge, bridge);
		if (ret) {
			DRM_DEV_ERROR(dp->dev,
				      "Failed to attach bridge to drm\n");
			bridge->next = NULL;
			return ret;
		}
	}

	return 0;
}