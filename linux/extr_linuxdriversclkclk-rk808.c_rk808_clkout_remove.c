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
struct rk808 {struct i2c_client* i2c; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct TYPE_4__ {struct device_node* of_node; } ;
struct i2c_client {TYPE_2__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 struct rk808* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_clk_del_provider (struct device_node*) ; 

__attribute__((used)) static int rk808_clkout_remove(struct platform_device *pdev)
{
	struct rk808 *rk808 = dev_get_drvdata(pdev->dev.parent);
	struct i2c_client *client = rk808->i2c;
	struct device_node *node = client->dev.of_node;

	of_clk_del_provider(node);

	return 0;
}