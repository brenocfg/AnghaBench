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
struct TYPE_4__ {int idx; int hw_key_idx; } ;
struct TYPE_3__ {TYPE_2__ global_wcid; int /*<<< orphan*/ * wcid; int /*<<< orphan*/  wcid_mask; int /*<<< orphan*/  state; } ;
struct mt7615_dev {TYPE_1__ mt76; int /*<<< orphan*/  token; int /*<<< orphan*/  token_lock; } ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ MT7615_WTBL_STA ; 
 int /*<<< orphan*/  MT76_STATE_INITIALIZED ; 
 int /*<<< orphan*/  MT_INT_SOURCE_CSR ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int mt7615_dma_init (struct mt7615_dev*) ; 
 int mt7615_eeprom_init (struct mt7615_dev*) ; 
 int /*<<< orphan*/  mt7615_mac_init (struct mt7615_dev*) ; 
 int /*<<< orphan*/  mt7615_mcu_ctrl_pm_state (struct mt7615_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7615_mcu_del_wtbl_all (struct mt7615_dev*) ; 
 int mt7615_mcu_init (struct mt7615_dev*) ; 
 int /*<<< orphan*/  mt7615_mcu_set_eeprom (struct mt7615_dev*) ; 
 int /*<<< orphan*/  mt7615_phy_init (struct mt7615_dev*) ; 
 int mt76_wcid_alloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mt76_wr (struct mt7615_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt7615_init_hardware(struct mt7615_dev *dev)
{
	int ret, idx;

	mt76_wr(dev, MT_INT_SOURCE_CSR, ~0);

	spin_lock_init(&dev->token_lock);
	idr_init(&dev->token);

	ret = mt7615_eeprom_init(dev);
	if (ret < 0)
		return ret;

	ret = mt7615_dma_init(dev);
	if (ret)
		return ret;

	set_bit(MT76_STATE_INITIALIZED, &dev->mt76.state);

	ret = mt7615_mcu_init(dev);
	if (ret)
		return ret;

	mt7615_mcu_set_eeprom(dev);
	mt7615_mac_init(dev);
	mt7615_phy_init(dev);
	mt7615_mcu_ctrl_pm_state(dev, 0);
	mt7615_mcu_del_wtbl_all(dev);

	/* Beacon and mgmt frames should occupy wcid 0 */
	idx = mt76_wcid_alloc(dev->mt76.wcid_mask, MT7615_WTBL_STA - 1);
	if (idx)
		return -ENOSPC;

	dev->mt76.global_wcid.idx = idx;
	dev->mt76.global_wcid.hw_key_idx = -1;
	rcu_assign_pointer(dev->mt76.wcid[idx], &dev->mt76.global_wcid);

	return 0;
}