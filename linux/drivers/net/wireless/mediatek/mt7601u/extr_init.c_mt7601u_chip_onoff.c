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
typedef  int u32 ;
struct mt7601u_dev {int /*<<< orphan*/  hw_atomic_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_WLAN_FUN_CTRL ; 
 int MT_WLAN_FUN_CTRL_FRC_WL_ANT_SEL ; 
 int MT_WLAN_FUN_CTRL_GPIO_OUT_EN ; 
 int MT_WLAN_FUN_CTRL_WLAN_EN ; 
 int MT_WLAN_FUN_CTRL_WLAN_RESET ; 
 int MT_WLAN_FUN_CTRL_WLAN_RESET_RF ; 
 int mt7601u_rr (struct mt7601u_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7601u_set_wlan_state (struct mt7601u_dev*,int,int) ; 
 int /*<<< orphan*/  mt7601u_wr (struct mt7601u_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void mt7601u_chip_onoff(struct mt7601u_dev *dev, bool enable, bool reset)
{
	u32 val;

	mutex_lock(&dev->hw_atomic_mutex);

	val = mt7601u_rr(dev, MT_WLAN_FUN_CTRL);

	if (reset) {
		val |= MT_WLAN_FUN_CTRL_GPIO_OUT_EN;
		val &= ~MT_WLAN_FUN_CTRL_FRC_WL_ANT_SEL;

		if (val & MT_WLAN_FUN_CTRL_WLAN_EN) {
			val |= (MT_WLAN_FUN_CTRL_WLAN_RESET |
				MT_WLAN_FUN_CTRL_WLAN_RESET_RF);
			mt7601u_wr(dev, MT_WLAN_FUN_CTRL, val);
			udelay(20);

			val &= ~(MT_WLAN_FUN_CTRL_WLAN_RESET |
				 MT_WLAN_FUN_CTRL_WLAN_RESET_RF);
		}
	}

	mt7601u_wr(dev, MT_WLAN_FUN_CTRL, val);
	udelay(20);

	mt7601u_set_wlan_state(dev, val, enable);

	mutex_unlock(&dev->hw_atomic_mutex);
}