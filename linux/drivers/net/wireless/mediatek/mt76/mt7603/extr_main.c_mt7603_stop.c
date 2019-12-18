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
struct TYPE_2__ {int /*<<< orphan*/  mac_work; int /*<<< orphan*/  state; } ;
struct mt7603_dev {TYPE_1__ mt76; } ;
struct ieee80211_hw {struct mt7603_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT76_STATE_RUNNING ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt7603_mac_stop (struct mt7603_dev*) ; 

__attribute__((used)) static void
mt7603_stop(struct ieee80211_hw *hw)
{
	struct mt7603_dev *dev = hw->priv;

	clear_bit(MT76_STATE_RUNNING, &dev->mt76.state);
	cancel_delayed_work_sync(&dev->mt76.mac_work);
	mt7603_mac_stop(dev);
}