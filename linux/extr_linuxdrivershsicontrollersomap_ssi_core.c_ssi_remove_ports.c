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
struct platform_device {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  OF_POPULATED ; 
 int /*<<< orphan*/  of_device_unregister (struct platform_device*) ; 
 int /*<<< orphan*/  of_node_clear_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int ssi_remove_ports(struct device *dev, void *c)
{
	struct platform_device *pdev = to_platform_device(dev);

	if (!dev->of_node)
		return 0;

	of_node_clear_flag(dev->of_node, OF_POPULATED);
	of_device_unregister(pdev);

	return 0;
}