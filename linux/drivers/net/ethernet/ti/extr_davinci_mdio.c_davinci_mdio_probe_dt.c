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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mdio_platform_data {int /*<<< orphan*/  bus_freq; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int davinci_mdio_probe_dt(struct mdio_platform_data *data,
			 struct platform_device *pdev)
{
	struct device_node *node = pdev->dev.of_node;
	u32 prop;

	if (!node)
		return -EINVAL;

	if (of_property_read_u32(node, "bus_freq", &prop)) {
		dev_err(&pdev->dev, "Missing bus_freq property in the DT.\n");
		return -EINVAL;
	}
	data->bus_freq = prop;

	return 0;
}