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
struct device {scalar_t__ of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  OF_POPULATED ; 
 int /*<<< orphan*/  of_device_unregister (struct platform_device*) ; 
 int /*<<< orphan*/  of_node_clear_flag (scalar_t__,int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int sbefifo_unregister_child(struct device *dev, void *data)
{
	struct platform_device *child = to_platform_device(dev);

	of_device_unregister(child);
	if (dev->of_node)
		of_node_clear_flag(dev->of_node, OF_POPULATED);

	return 0;
}