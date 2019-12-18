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
struct mt76x02_dev {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  CFG ; 
 int /*<<< orphan*/  MT_VEND_ADDR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_clear (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_set (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void mt76x2u_power_on_rf_patch(struct mt76x02_dev *dev)
{
	mt76_set(dev, MT_VEND_ADDR(CFG, 0x130), BIT(0) | BIT(16));
	udelay(1);

	mt76_clear(dev, MT_VEND_ADDR(CFG, 0x1c), 0xff);
	mt76_set(dev, MT_VEND_ADDR(CFG, 0x1c), 0x30);

	mt76_wr(dev, MT_VEND_ADDR(CFG, 0x14), 0x484f);
	udelay(1);

	mt76_set(dev, MT_VEND_ADDR(CFG, 0x130), BIT(17));
	usleep_range(150, 200);

	mt76_clear(dev, MT_VEND_ADDR(CFG, 0x130), BIT(16));
	usleep_range(50, 100);

	mt76_set(dev, MT_VEND_ADDR(CFG, 0x14c), BIT(19) | BIT(20));
}