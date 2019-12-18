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
struct gbe_slave {int /*<<< orphan*/  slave_list; scalar_t__ phy; } ;
struct gbe_priv {scalar_t__ dummy_ndev; int /*<<< orphan*/  secondary_slaves; } ;

/* Variables and functions */
 struct gbe_slave* first_sec_slave (struct gbe_priv*) ; 
 int /*<<< orphan*/  free_netdev (scalar_t__) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_disconnect (scalar_t__) ; 

__attribute__((used)) static void free_secondary_ports(struct gbe_priv *gbe_dev)
{
	struct gbe_slave *slave;

	while (!list_empty(&gbe_dev->secondary_slaves)) {
		slave = first_sec_slave(gbe_dev);

		if (slave->phy)
			phy_disconnect(slave->phy);
		list_del(&slave->slave_list);
	}
	if (gbe_dev->dummy_ndev)
		free_netdev(gbe_dev->dummy_ndev);
}