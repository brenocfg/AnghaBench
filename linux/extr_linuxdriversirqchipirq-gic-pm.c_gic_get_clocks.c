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
struct gic_clk_data {unsigned int num_clocks; int /*<<< orphan*/ * clocks; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 int of_pm_clk_add_clk (struct device*,int /*<<< orphan*/ ) ; 
 int pm_clk_create (struct device*) ; 
 int /*<<< orphan*/  pm_clk_destroy (struct device*) ; 

__attribute__((used)) static int gic_get_clocks(struct device *dev, const struct gic_clk_data *data)
{
	unsigned int i;
	int ret;

	if (!dev || !data)
		return -EINVAL;

	ret = pm_clk_create(dev);
	if (ret)
		return ret;

	for (i = 0; i < data->num_clocks; i++) {
		ret = of_pm_clk_add_clk(dev, data->clocks[i]);
		if (ret) {
			dev_err(dev, "failed to add clock %s\n",
				data->clocks[i]);
			pm_clk_destroy(dev);
			return ret;
		}
	}

	return 0;
}