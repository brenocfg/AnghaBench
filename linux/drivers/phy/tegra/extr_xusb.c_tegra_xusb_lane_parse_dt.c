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
struct tegra_xusb_lane {int function; TYPE_2__* soc; TYPE_1__* pad; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  num_funcs; int /*<<< orphan*/  funcs; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,char const*,struct device_node*) ; 
 int match_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int of_property_read_string (struct device_node*,char*,char const**) ; 

int tegra_xusb_lane_parse_dt(struct tegra_xusb_lane *lane,
			     struct device_node *np)
{
	struct device *dev = &lane->pad->dev;
	const char *function;
	int err;

	err = of_property_read_string(np, "nvidia,function", &function);
	if (err < 0)
		return err;

	err = match_string(lane->soc->funcs, lane->soc->num_funcs, function);
	if (err < 0) {
		dev_err(dev, "invalid function \"%s\" for lane \"%pOFn\"\n",
			function, np);
		return err;
	}

	lane->function = err;

	return 0;
}