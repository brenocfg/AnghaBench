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
typedef  int u32 ;
struct TYPE_2__ {int chainmask; int antenna_mask; int /*<<< orphan*/  mutex; } ;
struct mt76x02_dev {TYPE_1__ mt76; } ;
struct ieee80211_hw {struct mt76x02_dev* priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mt76_set_stream_caps (TYPE_1__*,int) ; 
 int /*<<< orphan*/  mt76x2_phy_set_antenna (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt76x2_set_antenna(struct ieee80211_hw *hw, u32 tx_ant,
			      u32 rx_ant)
{
	struct mt76x02_dev *dev = hw->priv;

	if (!tx_ant || tx_ant > 3 || tx_ant != rx_ant)
		return -EINVAL;

	mutex_lock(&dev->mt76.mutex);

	dev->mt76.chainmask = (tx_ant == 3) ? 0x202 : 0x101;
	dev->mt76.antenna_mask = tx_ant;

	mt76_set_stream_caps(&dev->mt76, true);
	mt76x2_phy_set_antenna(dev);

	mutex_unlock(&dev->mt76.mutex);

	return 0;
}