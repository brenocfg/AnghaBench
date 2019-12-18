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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct mt76x02_dev {TYPE_1__ mt76; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_CMB_CTRL ; 
 int MT_CMB_CTRL_PLL_LD ; 
 int MT_CMB_CTRL_XTAL_RDY ; 
 int /*<<< orphan*/  MT_WLAN_FUN_CTRL ; 
 int MT_WLAN_FUN_CTRL_WLAN_CLK_EN ; 
 int MT_WLAN_FUN_CTRL_WLAN_EN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mt76_poll (struct mt76x02_dev*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
mt76x0_set_wlan_state(struct mt76x02_dev *dev, u32 val, bool enable)
{
	u32 mask = MT_CMB_CTRL_XTAL_RDY | MT_CMB_CTRL_PLL_LD;

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

	mt76_wr(dev, MT_WLAN_FUN_CTRL, val);
	udelay(20);

	/* Note: vendor driver tries to disable/enable wlan here and retry
	 *       but the code which does it is so buggy it must have never
	 *       triggered, so don't bother.
	 */
	if (enable && !mt76_poll(dev, MT_CMB_CTRL, mask, mask, 2000))
		dev_err(dev->mt76.dev, "PLL and XTAL check failed\n");
}