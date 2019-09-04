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
struct hdmi_context {TYPE_2__* drv_data; struct clk** clk_muxes; struct device* dev; } ;
struct device {int dummy; } ;
struct clk {int dummy; } ;
struct TYPE_3__ {int count; int /*<<< orphan*/ * data; } ;
struct TYPE_4__ {TYPE_1__ clk_muxes; } ;

/* Variables and functions */
 int clk_set_parent (struct clk*,struct clk*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hdmi_clk_set_parents(struct hdmi_context *hdata, bool to_phy)
{
	struct device *dev = hdata->dev;
	int ret = 0;
	int i;

	for (i = 0; i < hdata->drv_data->clk_muxes.count; i += 3) {
		struct clk **c = &hdata->clk_muxes[i];

		ret = clk_set_parent(c[2], c[to_phy]);
		if (!ret)
			continue;

		dev_err(dev, "Cannot set clock parent of '%s' to '%s', %d\n",
			hdata->drv_data->clk_muxes.data[i + 2],
			hdata->drv_data->clk_muxes.data[i + to_phy], ret);
	}

	return ret;
}