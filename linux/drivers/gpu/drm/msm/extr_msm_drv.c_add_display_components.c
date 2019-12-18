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
struct device {int /*<<< orphan*/  of_node; } ;
struct component_match {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*) ; 
 int ENODEV ; 
 int add_components_mdp (struct device*,struct component_match**) ; 
 int /*<<< orphan*/  compare_name_mdp ; 
 int /*<<< orphan*/  compare_of ; 
 struct device* device_find_child (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_of_component_match_add (struct device*,struct component_match**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ of_device_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_platform_depopulate (struct device*) ; 
 int of_platform_populate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 

__attribute__((used)) static int add_display_components(struct device *dev,
				  struct component_match **matchptr)
{
	struct device *mdp_dev;
	int ret;

	/*
	 * MDP5/DPU based devices don't have a flat hierarchy. There is a top
	 * level parent: MDSS, and children: MDP5/DPU, DSI, HDMI, eDP etc.
	 * Populate the children devices, find the MDP5/DPU node, and then add
	 * the interfaces to our components list.
	 */
	if (of_device_is_compatible(dev->of_node, "qcom,mdss") ||
	    of_device_is_compatible(dev->of_node, "qcom,sdm845-mdss")) {
		ret = of_platform_populate(dev->of_node, NULL, NULL, dev);
		if (ret) {
			DRM_DEV_ERROR(dev, "failed to populate children devices\n");
			return ret;
		}

		mdp_dev = device_find_child(dev, NULL, compare_name_mdp);
		if (!mdp_dev) {
			DRM_DEV_ERROR(dev, "failed to find MDSS MDP node\n");
			of_platform_depopulate(dev);
			return -ENODEV;
		}

		put_device(mdp_dev);

		/* add the MDP component itself */
		drm_of_component_match_add(dev, matchptr, compare_of,
					   mdp_dev->of_node);
	} else {
		/* MDP4 */
		mdp_dev = dev;
	}

	ret = add_components_mdp(mdp_dev, matchptr);
	if (ret)
		of_platform_depopulate(dev);

	return ret;
}