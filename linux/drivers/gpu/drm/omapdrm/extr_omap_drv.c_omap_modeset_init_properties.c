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
struct omap_drm_private {int /*<<< orphan*/  zorder_prop; int /*<<< orphan*/  dispc; TYPE_1__* dispc_ops; } ;
struct drm_device {struct omap_drm_private* dev_private; } ;
struct TYPE_2__ {unsigned int (* get_num_ovls ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  drm_property_create_range (struct drm_device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_modeset_init_properties(struct drm_device *dev)
{
	struct omap_drm_private *priv = dev->dev_private;
	unsigned int num_planes = priv->dispc_ops->get_num_ovls(priv->dispc);

	priv->zorder_prop = drm_property_create_range(dev, 0, "zorder", 0,
						      num_planes - 1);
	if (!priv->zorder_prop)
		return -ENOMEM;

	return 0;
}