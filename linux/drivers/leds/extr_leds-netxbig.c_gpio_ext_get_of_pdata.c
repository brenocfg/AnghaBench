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
struct netxbig_gpio_ext {int* addr; int num_addr; int* data; int num_data; int enable; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 int of_get_named_gpio (struct device_node*,char*,int) ; 
 int of_gpio_named_count (struct device_node*,char*) ; 

__attribute__((used)) static int gpio_ext_get_of_pdata(struct device *dev, struct device_node *np,
				 struct netxbig_gpio_ext *gpio_ext)
{
	int *addr, *data;
	int num_addr, num_data;
	int ret;
	int i;

	ret = of_gpio_named_count(np, "addr-gpios");
	if (ret < 0) {
		dev_err(dev,
			"Failed to count GPIOs in DT property addr-gpios\n");
		return ret;
	}
	num_addr = ret;
	addr = devm_kcalloc(dev, num_addr, sizeof(*addr), GFP_KERNEL);
	if (!addr)
		return -ENOMEM;

	for (i = 0; i < num_addr; i++) {
		ret = of_get_named_gpio(np, "addr-gpios", i);
		if (ret < 0)
			return ret;
		addr[i] = ret;
	}
	gpio_ext->addr = addr;
	gpio_ext->num_addr = num_addr;

	ret = of_gpio_named_count(np, "data-gpios");
	if (ret < 0) {
		dev_err(dev,
			"Failed to count GPIOs in DT property data-gpios\n");
		return ret;
	}
	num_data = ret;
	data = devm_kcalloc(dev, num_data, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	for (i = 0; i < num_data; i++) {
		ret = of_get_named_gpio(np, "data-gpios", i);
		if (ret < 0)
			return ret;
		data[i] = ret;
	}
	gpio_ext->data = data;
	gpio_ext->num_data = num_data;

	ret = of_get_named_gpio(np, "enable-gpio", 0);
	if (ret < 0) {
		dev_err(dev,
			"Failed to get GPIO from DT property enable-gpio\n");
		return ret;
	}
	gpio_ext->enable = ret;

	return 0;
}