#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rcar_gen2_phy_driver {int num_channels; TYPE_2__* channels; } ;
struct phy {int dummy; } ;
struct of_phandle_args {int* args; struct device_node* np; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* phys; struct device_node* of_node; } ;
struct TYPE_3__ {struct phy* phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 struct phy* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct rcar_gen2_phy_driver* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static struct phy *rcar_gen2_phy_xlate(struct device *dev,
				       struct of_phandle_args *args)
{
	struct rcar_gen2_phy_driver *drv;
	struct device_node *np = args->np;
	int i;

	drv = dev_get_drvdata(dev);
	if (!drv)
		return ERR_PTR(-EINVAL);

	for (i = 0; i < drv->num_channels; i++) {
		if (np == drv->channels[i].of_node)
			break;
	}

	if (i >= drv->num_channels || args->args[0] >= 2)
		return ERR_PTR(-ENODEV);

	return drv->channels[i].phys[args->args[0]].phy;
}