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
typedef  int /*<<< orphan*/  u16 ;
struct mii_bus {struct mdio_mux_child_bus* priv; } ;
struct mdio_mux_parent_bus {int (* switch_fn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_1__* mii_bus; int /*<<< orphan*/  current_child; int /*<<< orphan*/  switch_data; } ;
struct mdio_mux_child_bus {int /*<<< orphan*/  bus_number; struct mdio_mux_parent_bus* parent; } ;
struct TYPE_2__ {int (* write ) (TYPE_1__*,int,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  mdio_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_MUTEX_MUX ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mdio_mux_write(struct mii_bus *bus, int phy_id,
			  int regnum, u16 val)
{
	struct mdio_mux_child_bus *cb = bus->priv;
	struct mdio_mux_parent_bus *pb = cb->parent;

	int r;

	mutex_lock_nested(&pb->mii_bus->mdio_lock, MDIO_MUTEX_MUX);
	r = pb->switch_fn(pb->current_child, cb->bus_number, pb->switch_data);
	if (r)
		goto out;

	pb->current_child = cb->bus_number;

	r = pb->mii_bus->write(pb->mii_bus, phy_id, regnum, val);
out:
	mutex_unlock(&pb->mii_bus->mdio_lock);

	return r;
}