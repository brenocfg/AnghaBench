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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct atl2_adapter {int /*<<< orphan*/  hw; int /*<<< orphan*/  flags; struct net_device* netdev; } ;

/* Variables and functions */
 int ATL2_READ_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATL2_WRITE_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int EIO ; 
 int MASTER_CTRL_MANUAL_INT ; 
 int /*<<< orphan*/  REG_MASTER_CTRL ; 
 int /*<<< orphan*/  __ATL2_DOWN ; 
 scalar_t__ atl2_configure (struct atl2_adapter*) ; 
 int atl2_init_hw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atl2_irq_enable (struct atl2_adapter*) ; 
 int /*<<< orphan*/  atl2_restore_vlan (struct atl2_adapter*) ; 
 int /*<<< orphan*/  atl2_set_multi (struct net_device*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_ring_ptrs (struct atl2_adapter*) ; 

__attribute__((used)) static int atl2_up(struct atl2_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	int err = 0;
	u32 val;

	/* hardware has been reset, we need to reload some things */

	err = atl2_init_hw(&adapter->hw);
	if (err) {
		err = -EIO;
		return err;
	}

	atl2_set_multi(netdev);
	init_ring_ptrs(adapter);

	atl2_restore_vlan(adapter);

	if (atl2_configure(adapter)) {
		err = -EIO;
		goto err_up;
	}

	clear_bit(__ATL2_DOWN, &adapter->flags);

	val = ATL2_READ_REG(&adapter->hw, REG_MASTER_CTRL);
	ATL2_WRITE_REG(&adapter->hw, REG_MASTER_CTRL, val |
		MASTER_CTRL_MANUAL_INT);

	atl2_irq_enable(adapter);

err_up:
	return err;
}