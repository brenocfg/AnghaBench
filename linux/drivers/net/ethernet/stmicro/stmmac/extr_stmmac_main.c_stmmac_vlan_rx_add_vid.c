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
struct TYPE_2__ {int /*<<< orphan*/  vlhash; } ;
struct stmmac_priv {int /*<<< orphan*/  active_vlans; TYPE_1__ dma_cap; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ ETH_P_8021AD ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stmmac_vlan_update (struct stmmac_priv*,int) ; 

__attribute__((used)) static int stmmac_vlan_rx_add_vid(struct net_device *ndev, __be16 proto, u16 vid)
{
	struct stmmac_priv *priv = netdev_priv(ndev);
	bool is_double = false;
	int ret;

	if (!priv->dma_cap.vlhash)
		return -EOPNOTSUPP;
	if (be16_to_cpu(proto) == ETH_P_8021AD)
		is_double = true;

	set_bit(vid, priv->active_vlans);
	ret = stmmac_vlan_update(priv, is_double);
	if (ret) {
		clear_bit(vid, priv->active_vlans);
		return ret;
	}

	return ret;
}