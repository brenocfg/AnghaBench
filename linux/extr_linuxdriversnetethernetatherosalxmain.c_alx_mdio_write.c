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
struct net_device {int dummy; } ;
struct TYPE_2__ {int prtad; } ;
struct alx_hw {TYPE_1__ mdio; } ;
struct alx_priv {struct alx_hw hw; } ;

/* Variables and functions */
 int EINVAL ; 
 int MDIO_DEVAD_NONE ; 
 int alx_write_phy_ext (struct alx_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int alx_write_phy_reg (struct alx_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct alx_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int alx_mdio_write(struct net_device *netdev,
			  int prtad, int devad, u16 addr, u16 val)
{
	struct alx_priv *alx = netdev_priv(netdev);
	struct alx_hw *hw = &alx->hw;

	if (prtad != hw->mdio.prtad)
		return -EINVAL;

	if (devad == MDIO_DEVAD_NONE)
		return alx_write_phy_reg(hw, addr, val);

	return alx_write_phy_ext(hw, devad, addr, val);
}