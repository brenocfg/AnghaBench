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
struct mt7601u_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT7601U_STATE_WLAN_RUNNING ; 
 int /*<<< orphan*/  MT_CMB_CTRL ; 
 int MT_CMB_CTRL_PLL_LD ; 
 int MT_CMB_CTRL_XTAL_RDY ; 
 int /*<<< orphan*/  MT_WLAN_FUN_CTRL ; 
 int MT_WLAN_FUN_CTRL_WLAN_CLK_EN ; 
 int MT_WLAN_FUN_CTRL_WLAN_EN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int mt7601u_rr (struct mt7601u_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7601u_wr (struct mt7601u_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
mt7601u_set_wlan_state(struct mt7601u_dev *dev, u32 val, bool enable)
{
	int i;

	/* Note: we don't turn off WLAN_CLK because that makes the device
	 *	 not respond properly on the probe path.
	 *	 In case anyone (PSM?) wants to use this function we can
	 *	 bring the clock stuff back and fixup the probe path.
	 */

	if (enable)
		val |= (MT_WLAN_FUN_CTRL_WLAN_EN |
			MT_WLAN_FUN_CTRL_WLAN_CLK_EN);
	else
		val &= ~(MT_WLAN_FUN_CTRL_WLAN_EN);

	mt7601u_wr(dev, MT_WLAN_FUN_CTRL, val);
	udelay(20);

	if (enable) {
		set_bit(MT7601U_STATE_WLAN_RUNNING, &dev->state);
	} else {
		clear_bit(MT7601U_STATE_WLAN_RUNNING, &dev->state);
		return;
	}

	for (i = 200; i; i--) {
		val = mt7601u_rr(dev, MT_CMB_CTRL);

		if (val & MT_CMB_CTRL_XTAL_RDY && val & MT_CMB_CTRL_PLL_LD)
			break;

		udelay(20);
	}

	/* Note: vendor driver tries to disable/enable wlan here and retry
	 *       but the code which does it is so buggy it must have never
	 *       triggered, so don't bother.
	 */
	if (!i)
		dev_err(dev->dev, "Error: PLL and XTAL check failed!\n");
}