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
struct max8925_platform_data {int /*<<< orphan*/  tsc_irq; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int max8925_dt_init(struct device_node *np, struct device *dev,
			   struct max8925_platform_data *pdata)
{
	int ret;

	ret = of_property_read_u32(np, "maxim,tsc-irq", &pdata->tsc_irq);
	if (ret) {
		dev_err(dev, "Not found maxim,tsc-irq property\n");
		return -EINVAL;
	}
	return 0;
}