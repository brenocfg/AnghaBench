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
struct enic {int /*<<< orphan*/  devcmd_lock; TYPE_1__* netdev; int /*<<< orphan*/  vdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int vnic_dev_add_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int enic_dev_add_station_addr(struct enic *enic)
{
	int err;

	if (!is_valid_ether_addr(enic->netdev->dev_addr))
		return -EADDRNOTAVAIL;

	spin_lock_bh(&enic->devcmd_lock);
	err = vnic_dev_add_addr(enic->vdev, enic->netdev->dev_addr);
	spin_unlock_bh(&enic->devcmd_lock);

	return err;
}