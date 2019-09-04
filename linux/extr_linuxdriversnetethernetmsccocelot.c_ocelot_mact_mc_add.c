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
struct ocelot_port {int /*<<< orphan*/  pvid; int /*<<< orphan*/  mc; struct ocelot* ocelot; } ;
struct ocelot {int dummy; } ;
struct netdev_hw_addr {int /*<<< orphan*/  addr; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ENTRYTYPE_LOCKED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PGID_CPU ; 
 struct netdev_hw_addr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct netdev_hw_addr*,struct netdev_hw_addr*,int) ; 
 int /*<<< orphan*/  ocelot_mact_learn (struct ocelot*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocelot_mact_mc_add(struct ocelot_port *port,
			      struct netdev_hw_addr *hw_addr)
{
	struct ocelot *ocelot = port->ocelot;
	struct netdev_hw_addr *ha = kzalloc(sizeof(*ha), GFP_KERNEL);

	if (!ha)
		return -ENOMEM;

	memcpy(ha, hw_addr, sizeof(*ha));
	list_add_tail(&ha->list, &port->mc);

	ocelot_mact_learn(ocelot, PGID_CPU, ha->addr, port->pvid,
			  ENTRYTYPE_LOCKED);

	return 0;
}