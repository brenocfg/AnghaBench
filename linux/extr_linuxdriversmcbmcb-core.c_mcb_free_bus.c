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
struct mcb_bus {int /*<<< orphan*/  bus_nr; int /*<<< orphan*/  carrier; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mcb_bus*) ; 
 int /*<<< orphan*/  mcb_ida ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ ) ; 
 struct mcb_bus* to_mcb_bus (struct device*) ; 

__attribute__((used)) static void mcb_free_bus(struct device *dev)
{
	struct mcb_bus *bus = to_mcb_bus(dev);

	put_device(bus->carrier);
	ida_simple_remove(&mcb_ida, bus->bus_nr);
	kfree(bus);
}