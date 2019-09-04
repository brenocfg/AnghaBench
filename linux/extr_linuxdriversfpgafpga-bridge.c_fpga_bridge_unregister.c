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
struct fpga_bridge {int /*<<< orphan*/  dev; TYPE_1__* br_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* fpga_bridge_remove ) (struct fpga_bridge*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct fpga_bridge*) ; 

void fpga_bridge_unregister(struct fpga_bridge *bridge)
{
	/*
	 * If the low level driver provides a method for putting bridge into
	 * a desired state upon unregister, do it.
	 */
	if (bridge->br_ops && bridge->br_ops->fpga_bridge_remove)
		bridge->br_ops->fpga_bridge_remove(bridge);

	device_unregister(&bridge->dev);
}