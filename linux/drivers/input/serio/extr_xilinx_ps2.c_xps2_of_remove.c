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
struct xps2data {int /*<<< orphan*/  dev; int /*<<< orphan*/  base_address; int /*<<< orphan*/  serio; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct xps2data*) ; 
 scalar_t__ of_address_to_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource*) ; 
 struct xps2data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  serio_unregister_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xps2_of_remove(struct platform_device *of_dev)
{
	struct xps2data *drvdata = platform_get_drvdata(of_dev);
	struct resource r_mem; /* IO mem resources */

	serio_unregister_port(drvdata->serio);
	iounmap(drvdata->base_address);

	/* Get iospace of the device */
	if (of_address_to_resource(of_dev->dev.of_node, 0, &r_mem))
		dev_err(drvdata->dev, "invalid address\n");
	else
		release_mem_region(r_mem.start, resource_size(&r_mem));

	kfree(drvdata);

	return 0;
}