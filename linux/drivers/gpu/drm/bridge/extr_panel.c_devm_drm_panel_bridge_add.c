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
typedef  int /*<<< orphan*/  u32 ;
struct drm_panel {int dummy; } ;
struct drm_bridge {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct drm_bridge* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct drm_bridge*) ; 
 int /*<<< orphan*/  devm_drm_panel_bridge_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct drm_bridge**) ; 
 struct drm_bridge** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct drm_bridge**) ; 
 struct drm_bridge* drm_panel_bridge_add (struct drm_panel*,int /*<<< orphan*/ ) ; 

struct drm_bridge *devm_drm_panel_bridge_add(struct device *dev,
					     struct drm_panel *panel,
					     u32 connector_type)
{
	struct drm_bridge **ptr, *bridge;

	ptr = devres_alloc(devm_drm_panel_bridge_release, sizeof(*ptr),
			   GFP_KERNEL);
	if (!ptr)
		return ERR_PTR(-ENOMEM);

	bridge = drm_panel_bridge_add(panel, connector_type);
	if (!IS_ERR(bridge)) {
		*ptr = bridge;
		devres_add(dev, ptr);
	} else {
		devres_free(ptr);
	}

	return bridge;
}