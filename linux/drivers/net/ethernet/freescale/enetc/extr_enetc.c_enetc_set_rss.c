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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct enetc_ndev_priv {int /*<<< orphan*/  num_rx_rings; TYPE_1__* si; } ;
struct enetc_hw {int dummy; } ;
struct TYPE_2__ {struct enetc_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENETC_SIMR ; 
 int /*<<< orphan*/  ENETC_SIMR_RSSE ; 
 int /*<<< orphan*/  ENETC_SIRBGCR ; 
 int /*<<< orphan*/  enetc_rd (struct enetc_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enetc_wr (struct enetc_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct enetc_ndev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int enetc_set_rss(struct net_device *ndev, int en)
{
	struct enetc_ndev_priv *priv = netdev_priv(ndev);
	struct enetc_hw *hw = &priv->si->hw;
	u32 reg;

	enetc_wr(hw, ENETC_SIRBGCR, priv->num_rx_rings);

	reg = enetc_rd(hw, ENETC_SIMR);
	reg &= ~ENETC_SIMR_RSSE;
	reg |= (en) ? ENETC_SIMR_RSSE : 0;
	enetc_wr(hw, ENETC_SIMR, reg);

	return 0;
}