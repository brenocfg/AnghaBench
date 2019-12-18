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
struct atl2_adapter {int /*<<< orphan*/  hw; int /*<<< orphan*/  watchdog_timer; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ATL2_READ_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATL2_WRITE_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int EBUSY ; 
 int EIO ; 
 int HZ ; 
 int MASTER_CTRL_MANUAL_INT ; 
 int /*<<< orphan*/  REG_MASTER_CTRL ; 
 int /*<<< orphan*/  __ATL2_DOWN ; 
 int /*<<< orphan*/  __ATL2_TESTING ; 
 scalar_t__ atl2_configure (struct atl2_adapter*) ; 
 int /*<<< orphan*/  atl2_free_ring_resources (struct atl2_adapter*) ; 
 int atl2_init_hw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atl2_irq_enable (struct atl2_adapter*) ; 
 int atl2_request_irq (struct atl2_adapter*) ; 
 int /*<<< orphan*/  atl2_reset_hw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atl2_restore_vlan (struct atl2_adapter*) ; 
 int /*<<< orphan*/  atl2_set_multi (struct net_device*) ; 
 int atl2_setup_ring_resources (struct atl2_adapter*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_ring_ptrs (struct atl2_adapter*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct atl2_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  round_jiffies (scalar_t__) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atl2_open(struct net_device *netdev)
{
	struct atl2_adapter *adapter = netdev_priv(netdev);
	int err;
	u32 val;

	/* disallow open during test */
	if (test_bit(__ATL2_TESTING, &adapter->flags))
		return -EBUSY;

	/* allocate transmit descriptors */
	err = atl2_setup_ring_resources(adapter);
	if (err)
		return err;

	err = atl2_init_hw(&adapter->hw);
	if (err) {
		err = -EIO;
		goto err_init_hw;
	}

	/* hardware has been reset, we need to reload some things */
	atl2_set_multi(netdev);
	init_ring_ptrs(adapter);

	atl2_restore_vlan(adapter);

	if (atl2_configure(adapter)) {
		err = -EIO;
		goto err_config;
	}

	err = atl2_request_irq(adapter);
	if (err)
		goto err_req_irq;

	clear_bit(__ATL2_DOWN, &adapter->flags);

	mod_timer(&adapter->watchdog_timer, round_jiffies(jiffies + 4*HZ));

	val = ATL2_READ_REG(&adapter->hw, REG_MASTER_CTRL);
	ATL2_WRITE_REG(&adapter->hw, REG_MASTER_CTRL,
		val | MASTER_CTRL_MANUAL_INT);

	atl2_irq_enable(adapter);

	return 0;

err_init_hw:
err_req_irq:
err_config:
	atl2_free_ring_resources(adapter);
	atl2_reset_hw(&adapter->hw);

	return err;
}