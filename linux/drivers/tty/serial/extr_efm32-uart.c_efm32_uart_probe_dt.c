#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {struct device_node* of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct TYPE_5__ {int line; } ;
struct TYPE_4__ {int location; } ;
struct efm32_uart_port {TYPE_2__ port; TYPE_1__ pdata; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  efm_debug (struct efm32_uart_port*,char*,...) ; 
 int of_alias_get_id (struct device_node*,char*) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 

__attribute__((used)) static int efm32_uart_probe_dt(struct platform_device *pdev,
		struct efm32_uart_port *efm_port)
{
	struct device_node *np = pdev->dev.of_node;
	u32 location;
	int ret;

	if (!np)
		return 1;

	ret = of_property_read_u32(np, "energymicro,location", &location);

	if (ret)
		/* fall back to wrongly namespaced property */
		ret = of_property_read_u32(np, "efm32,location", &location);

	if (ret)
		/* fall back to old and (wrongly) generic property "location" */
		ret = of_property_read_u32(np, "location", &location);

	if (!ret) {
		if (location > 5) {
			dev_err(&pdev->dev, "invalid location\n");
			return -EINVAL;
		}
		efm_debug(efm_port, "using location %u\n", location);
		efm_port->pdata.location = location;
	} else {
		efm_debug(efm_port, "fall back to location 0\n");
	}

	ret = of_alias_get_id(np, "serial");
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to get alias id: %d\n", ret);
		return ret;
	} else {
		efm_port->port.line = ret;
		return 0;
	}

}