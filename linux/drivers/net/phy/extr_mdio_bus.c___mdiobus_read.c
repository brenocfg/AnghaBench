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
typedef  int /*<<< orphan*/  u32 ;
struct mii_bus {int (* read ) (struct mii_bus*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  mdio_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int stub1 (struct mii_bus*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_mdio_access (struct mii_bus*,int,int,int /*<<< orphan*/ ,int,int) ; 

int __mdiobus_read(struct mii_bus *bus, int addr, u32 regnum)
{
	int retval;

	WARN_ON_ONCE(!mutex_is_locked(&bus->mdio_lock));

	retval = bus->read(bus, addr, regnum);

	trace_mdio_access(bus, 1, addr, regnum, retval, retval);

	return retval;
}