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
typedef  int /*<<< orphan*/  u16 ;
struct port_info {struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct adapter {int /*<<< orphan*/  mdio_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_MI1_ADDR ; 
 int /*<<< orphan*/  A_MI1_CFG ; 
 int /*<<< orphan*/  A_MI1_DATA ; 
 int /*<<< orphan*/  A_MI1_OP ; 
 int /*<<< orphan*/  F_BUSY ; 
 int /*<<< orphan*/  MDIO_ATTEMPTS ; 
 int M_ST ; 
 int V_MDI_OP (int) ; 
 int V_PHYADDR (int) ; 
 int V_REGADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_ST (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int t3_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_set_reg_field (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int t3_wait_op_done (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int t3_mi1_read(struct net_device *dev, int phy_addr, int mmd_addr,
		       u16 reg_addr)
{
	struct port_info *pi = netdev_priv(dev);
	struct adapter *adapter = pi->adapter;
	int ret;
	u32 addr = V_REGADDR(reg_addr) | V_PHYADDR(phy_addr);

	mutex_lock(&adapter->mdio_lock);
	t3_set_reg_field(adapter, A_MI1_CFG, V_ST(M_ST), V_ST(1));
	t3_write_reg(adapter, A_MI1_ADDR, addr);
	t3_write_reg(adapter, A_MI1_OP, V_MDI_OP(2));
	ret = t3_wait_op_done(adapter, A_MI1_OP, F_BUSY, 0, MDIO_ATTEMPTS, 10);
	if (!ret)
		ret = t3_read_reg(adapter, A_MI1_DATA);
	mutex_unlock(&adapter->mdio_lock);
	return ret;
}