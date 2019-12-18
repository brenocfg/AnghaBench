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
struct net_device {int /*<<< orphan*/  phydev; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  mtu; } ;
struct ag71xx {int /*<<< orphan*/  rx_buf_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  AG71XX_REG_MAC_MFL ; 
 scalar_t__ NET_IP_ALIGN ; 
 scalar_t__ NET_SKB_PAD ; 
 int /*<<< orphan*/  SKB_DATA_ALIGN (scalar_t__) ; 
 int ag71xx_hw_enable (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_hw_set_macaddr (struct ag71xx*,int /*<<< orphan*/ ) ; 
 unsigned int ag71xx_max_frame_len (int /*<<< orphan*/ ) ; 
 int ag71xx_phy_connect (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_rings_cleanup (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_wr (struct ag71xx*,int /*<<< orphan*/ ,unsigned int) ; 
 struct ag71xx* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ag71xx_open(struct net_device *ndev)
{
	struct ag71xx *ag = netdev_priv(ndev);
	unsigned int max_frame_len;
	int ret;

	max_frame_len = ag71xx_max_frame_len(ndev->mtu);
	ag->rx_buf_size =
		SKB_DATA_ALIGN(max_frame_len + NET_SKB_PAD + NET_IP_ALIGN);

	/* setup max frame length */
	ag71xx_wr(ag, AG71XX_REG_MAC_MFL, max_frame_len);
	ag71xx_hw_set_macaddr(ag, ndev->dev_addr);

	ret = ag71xx_hw_enable(ag);
	if (ret)
		goto err;

	ret = ag71xx_phy_connect(ag);
	if (ret)
		goto err;

	phy_start(ndev->phydev);

	return 0;

err:
	ag71xx_rings_cleanup(ag);
	return ret;
}