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
struct tegra_xusb_pad {struct phy** lanes; TYPE_1__* soc; } ;
struct TYPE_4__ {scalar_t__ of_node; } ;
struct phy {TYPE_2__ dev; } ;
struct of_phandle_args {scalar_t__ args_count; scalar_t__ np; } ;
struct device {int dummy; } ;
struct TYPE_3__ {unsigned int num_lanes; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 struct phy* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct tegra_xusb_pad* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static struct phy *tegra_xusb_pad_of_xlate(struct device *dev,
					   struct of_phandle_args *args)
{
	struct tegra_xusb_pad *pad = dev_get_drvdata(dev);
	struct phy *phy = NULL;
	unsigned int i;

	if (args->args_count != 0)
		return ERR_PTR(-EINVAL);

	for (i = 0; i < pad->soc->num_lanes; i++) {
		if (!pad->lanes[i])
			continue;

		if (pad->lanes[i]->dev.of_node == args->np) {
			phy = pad->lanes[i];
			break;
		}
	}

	if (phy == NULL)
		phy = ERR_PTR(-ENODEV);

	return phy;
}