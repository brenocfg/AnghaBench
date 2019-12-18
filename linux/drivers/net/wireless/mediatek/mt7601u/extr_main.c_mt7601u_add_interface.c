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
struct TYPE_2__ {unsigned int idx; int hw_key_idx; } ;
struct mt76_vif {unsigned int idx; TYPE_1__ group_wcid; } ;
struct mt7601u_dev {int* wcid_mask; int /*<<< orphan*/  macaddr; } ;
struct ieee80211_vif {int /*<<< orphan*/  addr; scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct mt7601u_dev* priv; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 unsigned int BITS_PER_LONG ; 
 int ENOSPC ; 
 unsigned int GROUP_WCID (unsigned int) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7601u_set_macaddr (struct mt7601u_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt7601u_add_interface(struct ieee80211_hw *hw,
				 struct ieee80211_vif *vif)
{
	struct mt7601u_dev *dev = hw->priv;
	struct mt76_vif *mvif = (struct mt76_vif *) vif->drv_priv;
	unsigned int idx = 0;
	unsigned int wcid = GROUP_WCID(idx);

	/* Note: for AP do the AP-STA things mt76 does:
	 *	- beacon offsets
	 *	- do mac address tricks
	 *	- shift vif idx
	 */
	mvif->idx = idx;

	if (!ether_addr_equal(dev->macaddr, vif->addr))
		mt7601u_set_macaddr(dev, vif->addr);

	if (dev->wcid_mask[wcid / BITS_PER_LONG] & BIT(wcid % BITS_PER_LONG))
		return -ENOSPC;
	dev->wcid_mask[wcid / BITS_PER_LONG] |= BIT(wcid % BITS_PER_LONG);
	mvif->group_wcid.idx = wcid;
	mvif->group_wcid.hw_key_idx = -1;

	return 0;
}