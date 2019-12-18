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
struct net_device {char* dev_addr; } ;
struct mtk_mac {struct mtk_eth* hw; int /*<<< orphan*/  id; } ;
struct mtk_eth {int /*<<< orphan*/  page_lock; TYPE_1__* soc; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  caps; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  MT7628_SDM_MAC_ADRH ; 
 int /*<<< orphan*/  MT7628_SDM_MAC_ADRL ; 
 int /*<<< orphan*/  MTK_GDMA_MAC_ADRH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTK_GDMA_MAC_ADRL (int /*<<< orphan*/ ) ; 
 scalar_t__ MTK_HAS_CAPS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTK_RESETTING ; 
 int /*<<< orphan*/  MTK_SOC_MT7628 ; 
 int eth_mac_addr (struct net_device*,void*) ; 
 int /*<<< orphan*/  mtk_w32 (struct mtk_eth*,char const,int /*<<< orphan*/ ) ; 
 struct mtk_mac* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_set_mac_address(struct net_device *dev, void *p)
{
	int ret = eth_mac_addr(dev, p);
	struct mtk_mac *mac = netdev_priv(dev);
	struct mtk_eth *eth = mac->hw;
	const char *macaddr = dev->dev_addr;

	if (ret)
		return ret;

	if (unlikely(test_bit(MTK_RESETTING, &mac->hw->state)))
		return -EBUSY;

	spin_lock_bh(&mac->hw->page_lock);
	if (MTK_HAS_CAPS(eth->soc->caps, MTK_SOC_MT7628)) {
		mtk_w32(mac->hw, (macaddr[0] << 8) | macaddr[1],
			MT7628_SDM_MAC_ADRH);
		mtk_w32(mac->hw, (macaddr[2] << 24) | (macaddr[3] << 16) |
			(macaddr[4] << 8) | macaddr[5],
			MT7628_SDM_MAC_ADRL);
	} else {
		mtk_w32(mac->hw, (macaddr[0] << 8) | macaddr[1],
			MTK_GDMA_MAC_ADRH(mac->id));
		mtk_w32(mac->hw, (macaddr[2] << 24) | (macaddr[3] << 16) |
			(macaddr[4] << 8) | macaddr[5],
			MTK_GDMA_MAC_ADRL(mac->id));
	}
	spin_unlock_bh(&mac->hw->page_lock);

	return 0;
}