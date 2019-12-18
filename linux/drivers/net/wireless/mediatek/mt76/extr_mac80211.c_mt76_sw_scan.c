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
typedef  int /*<<< orphan*/  u8 ;
struct mt76_dev {int /*<<< orphan*/  state; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct mt76_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT76_SCANNING ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void mt76_sw_scan(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
		  const u8 *mac)
{
	struct mt76_dev *dev = hw->priv;

	set_bit(MT76_SCANNING, &dev->state);
}