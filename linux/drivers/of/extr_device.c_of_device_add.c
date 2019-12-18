#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * of_node; } ;
struct platform_device {TYPE_1__ dev; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLATFORM_DEVID_NONE ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int device_add (TYPE_1__*) ; 
 int /*<<< orphan*/  of_node_to_nid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_dev_node (TYPE_1__*,int /*<<< orphan*/ ) ; 

int of_device_add(struct platform_device *ofdev)
{
	BUG_ON(ofdev->dev.of_node == NULL);

	/* name and id have to be set so that the platform bus doesn't get
	 * confused on matching */
	ofdev->name = dev_name(&ofdev->dev);
	ofdev->id = PLATFORM_DEVID_NONE;

	/*
	 * If this device has not binding numa node in devicetree, that is
	 * of_node_to_nid returns NUMA_NO_NODE. device_add will assume that this
	 * device is on the same node as the parent.
	 */
	set_dev_node(&ofdev->dev, of_node_to_nid(ofdev->dev.of_node));

	return device_add(&ofdev->dev);
}