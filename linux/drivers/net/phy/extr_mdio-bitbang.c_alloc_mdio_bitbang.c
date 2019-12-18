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
struct mii_bus {struct mdiobb_ctrl* priv; int /*<<< orphan*/  write; int /*<<< orphan*/  read; } ;
struct mdiobb_ctrl {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobb_read ; 
 int /*<<< orphan*/  mdiobb_write ; 
 struct mii_bus* mdiobus_alloc () ; 

struct mii_bus *alloc_mdio_bitbang(struct mdiobb_ctrl *ctrl)
{
	struct mii_bus *bus;

	bus = mdiobus_alloc();
	if (!bus)
		return NULL;

	__module_get(ctrl->ops->owner);

	bus->read = mdiobb_read;
	bus->write = mdiobb_write;
	bus->priv = ctrl;

	return bus;
}