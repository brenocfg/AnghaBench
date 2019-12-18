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
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
struct mt7615_dev {int scs_en; TYPE_1__ mt76; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_MIB_M0_MISC_CR ; 
 int /*<<< orphan*/  MT_WF_PHY_B0_MIN_PRI_PWR ; 
 int MT_WF_PHY_B0_PD_BLK ; 
 int /*<<< orphan*/  MT_WF_PHY_B1_MIN_PRI_PWR ; 
 int MT_WF_PHY_B1_PD_BLK ; 
 scalar_t__ is_mt7622 (TYPE_1__*) ; 
 int /*<<< orphan*/  mt7615_mac_set_default_sensitivity (struct mt7615_dev*) ; 
 int /*<<< orphan*/  mt76_clear (struct mt7615_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_set (struct mt7615_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void mt7615_mac_set_scs(struct mt7615_dev *dev, bool enable)
{
	mutex_lock(&dev->mt76.mutex);

	if (dev->scs_en == enable)
		goto out;

	if (enable) {
		/* DBDC not supported */
		mt76_set(dev, MT_WF_PHY_B0_MIN_PRI_PWR,
			 MT_WF_PHY_B0_PD_BLK);
		if (is_mt7622(&dev->mt76)) {
			mt76_set(dev, MT_MIB_M0_MISC_CR, 0x7 << 8);
			mt76_set(dev, MT_MIB_M0_MISC_CR, 0x7);
		}
	} else {
		mt76_clear(dev, MT_WF_PHY_B0_MIN_PRI_PWR,
			   MT_WF_PHY_B0_PD_BLK);
		mt76_clear(dev, MT_WF_PHY_B1_MIN_PRI_PWR,
			   MT_WF_PHY_B1_PD_BLK);
	}

	mt7615_mac_set_default_sensitivity(dev);
	dev->scs_en = enable;

out:
	mutex_unlock(&dev->mt76.mutex);
}