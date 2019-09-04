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
struct v4l2_subdev {int dummy; } ;
struct device {int dummy; } ;
struct csiphy_device {int /*<<< orphan*/  clock; int /*<<< orphan*/  nclocks; int /*<<< orphan*/  irq; TYPE_2__* ops; TYPE_1__* camss; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* hw_version_read ) (struct csiphy_device*,struct device*) ;int /*<<< orphan*/  (* reset ) (struct csiphy_device*) ;} ;
struct TYPE_3__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  camss_disable_clocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int camss_enable_clocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct device*) ; 
 int csiphy_set_clock_rates (struct csiphy_device*) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct csiphy_device*) ; 
 int /*<<< orphan*/  stub2 (struct csiphy_device*,struct device*) ; 
 struct csiphy_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int csiphy_set_power(struct v4l2_subdev *sd, int on)
{
	struct csiphy_device *csiphy = v4l2_get_subdevdata(sd);
	struct device *dev = csiphy->camss->dev;

	if (on) {
		int ret;

		ret = pm_runtime_get_sync(dev);
		if (ret < 0)
			return ret;

		ret = csiphy_set_clock_rates(csiphy);
		if (ret < 0) {
			pm_runtime_put_sync(dev);
			return ret;
		}

		ret = camss_enable_clocks(csiphy->nclocks, csiphy->clock, dev);
		if (ret < 0) {
			pm_runtime_put_sync(dev);
			return ret;
		}

		enable_irq(csiphy->irq);

		csiphy->ops->reset(csiphy);

		csiphy->ops->hw_version_read(csiphy, dev);
	} else {
		disable_irq(csiphy->irq);

		camss_disable_clocks(csiphy->nclocks, csiphy->clock);

		pm_runtime_put_sync(dev);
	}

	return 0;
}