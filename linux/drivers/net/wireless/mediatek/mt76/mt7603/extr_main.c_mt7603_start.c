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
struct TYPE_3__ {int /*<<< orphan*/  work; } ;
struct TYPE_4__ {TYPE_1__ mac_work; int /*<<< orphan*/  state; int /*<<< orphan*/  survey_time; } ;
struct mt7603_dev {TYPE_2__ mt76; } ;
struct ieee80211_hw {struct mt7603_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT76_STATE_RUNNING ; 
 int /*<<< orphan*/  ktime_get_boottime () ; 
 int /*<<< orphan*/  mt7603_mac_start (struct mt7603_dev*) ; 
 int /*<<< orphan*/  mt7603_mac_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mt7603_start(struct ieee80211_hw *hw)
{
	struct mt7603_dev *dev = hw->priv;

	mt7603_mac_start(dev);
	dev->mt76.survey_time = ktime_get_boottime();
	set_bit(MT76_STATE_RUNNING, &dev->mt76.state);
	mt7603_mac_work(&dev->mt76.mac_work.work);

	return 0;
}