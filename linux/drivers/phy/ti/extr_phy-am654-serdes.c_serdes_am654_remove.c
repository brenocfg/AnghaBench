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
struct serdes_am654 {struct device_node* of_node; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_clk_del_provider (struct device_node*) ; 
 struct serdes_am654* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int serdes_am654_remove(struct platform_device *pdev)
{
	struct serdes_am654 *am654_phy = platform_get_drvdata(pdev);
	struct device_node *node = am654_phy->of_node;

	pm_runtime_disable(&pdev->dev);
	of_clk_del_provider(node);

	return 0;
}