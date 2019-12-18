#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ieee802154_hw {struct device* parent; int /*<<< orphan*/  flags; TYPE_2__* phy; struct hwsim_phy* priv; } ;
struct hwsim_pib {int dummy; } ;
struct hwsim_phy {int idx; struct ieee802154_hw* hw; int /*<<< orphan*/  list; int /*<<< orphan*/  edges; int /*<<< orphan*/  pib; } ;
struct genl_info {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int* channels; } ;
struct TYPE_4__ {int current_channel; int /*<<< orphan*/  perm_extended_addr; TYPE_1__ supported; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IEEE802154_HW_PROMISCUOUS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwsim_mcast_new_radio (struct genl_info*,struct hwsim_phy*) ; 
 int /*<<< orphan*/  hwsim_ops ; 
 int /*<<< orphan*/  hwsim_phys ; 
 int /*<<< orphan*/  hwsim_phys_lock ; 
 int /*<<< orphan*/  hwsim_radio_idx ; 
 int hwsim_subscribe_all_others (struct hwsim_phy*) ; 
 struct ieee802154_hw* ieee802154_alloc_hw (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee802154_free_hw (struct ieee802154_hw*) ; 
 int /*<<< orphan*/  ieee802154_random_extended_addr (int /*<<< orphan*/ *) ; 
 int ieee802154_register_hw (struct ieee802154_hw*) ; 
 int /*<<< orphan*/  ieee802154_unregister_hw (struct ieee802154_hw*) ; 
 int /*<<< orphan*/  kfree (struct hwsim_pib*) ; 
 struct hwsim_pib* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct hwsim_pib*) ; 

__attribute__((used)) static int hwsim_add_one(struct genl_info *info, struct device *dev,
			 bool init)
{
	struct ieee802154_hw *hw;
	struct hwsim_phy *phy;
	struct hwsim_pib *pib;
	int idx;
	int err;

	idx = hwsim_radio_idx++;

	hw = ieee802154_alloc_hw(sizeof(*phy), &hwsim_ops);
	if (!hw)
		return -ENOMEM;

	phy = hw->priv;
	phy->hw = hw;

	/* 868 MHz BPSK	802.15.4-2003 */
	hw->phy->supported.channels[0] |= 1;
	/* 915 MHz BPSK	802.15.4-2003 */
	hw->phy->supported.channels[0] |= 0x7fe;
	/* 2.4 GHz O-QPSK 802.15.4-2003 */
	hw->phy->supported.channels[0] |= 0x7FFF800;
	/* 868 MHz ASK 802.15.4-2006 */
	hw->phy->supported.channels[1] |= 1;
	/* 915 MHz ASK 802.15.4-2006 */
	hw->phy->supported.channels[1] |= 0x7fe;
	/* 868 MHz O-QPSK 802.15.4-2006 */
	hw->phy->supported.channels[2] |= 1;
	/* 915 MHz O-QPSK 802.15.4-2006 */
	hw->phy->supported.channels[2] |= 0x7fe;
	/* 2.4 GHz CSS 802.15.4a-2007 */
	hw->phy->supported.channels[3] |= 0x3fff;
	/* UWB Sub-gigahertz 802.15.4a-2007 */
	hw->phy->supported.channels[4] |= 1;
	/* UWB Low band 802.15.4a-2007 */
	hw->phy->supported.channels[4] |= 0x1e;
	/* UWB High band 802.15.4a-2007 */
	hw->phy->supported.channels[4] |= 0xffe0;
	/* 750 MHz O-QPSK 802.15.4c-2009 */
	hw->phy->supported.channels[5] |= 0xf;
	/* 750 MHz MPSK 802.15.4c-2009 */
	hw->phy->supported.channels[5] |= 0xf0;
	/* 950 MHz BPSK 802.15.4d-2009 */
	hw->phy->supported.channels[6] |= 0x3ff;
	/* 950 MHz GFSK 802.15.4d-2009 */
	hw->phy->supported.channels[6] |= 0x3ffc00;

	ieee802154_random_extended_addr(&hw->phy->perm_extended_addr);

	/* hwsim phy channel 13 as default */
	hw->phy->current_channel = 13;
	pib = kzalloc(sizeof(*pib), GFP_KERNEL);
	if (!pib) {
		err = -ENOMEM;
		goto err_pib;
	}

	rcu_assign_pointer(phy->pib, pib);
	phy->idx = idx;
	INIT_LIST_HEAD(&phy->edges);

	hw->flags = IEEE802154_HW_PROMISCUOUS;
	hw->parent = dev;

	err = ieee802154_register_hw(hw);
	if (err)
		goto err_reg;

	mutex_lock(&hwsim_phys_lock);
	if (init) {
		err = hwsim_subscribe_all_others(phy);
		if (err < 0) {
			mutex_unlock(&hwsim_phys_lock);
			goto err_subscribe;
		}
	}
	list_add_tail(&phy->list, &hwsim_phys);
	mutex_unlock(&hwsim_phys_lock);

	hwsim_mcast_new_radio(info, phy);

	return idx;

err_subscribe:
	ieee802154_unregister_hw(phy->hw);
err_reg:
	kfree(pib);
err_pib:
	ieee802154_free_hw(phy->hw);
	return err;
}