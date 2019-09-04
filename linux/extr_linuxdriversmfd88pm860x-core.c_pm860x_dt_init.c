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
struct pm860x_platform_data {int irq_mode; scalar_t__ companion_addr; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 

__attribute__((used)) static int pm860x_dt_init(struct device_node *np,
				    struct device *dev,
				    struct pm860x_platform_data *pdata)
{
	int ret;

	if (of_get_property(np, "marvell,88pm860x-irq-read-clr", NULL))
		pdata->irq_mode = 1;
	ret = of_property_read_u32(np, "marvell,88pm860x-slave-addr",
				   &pdata->companion_addr);
	if (ret) {
		dev_err(dev,
			"Not found \"marvell,88pm860x-slave-addr\" property\n");
		pdata->companion_addr = 0;
	}
	return 0;
}