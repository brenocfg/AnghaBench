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
 int /*<<< orphan*/  mt76_clear (struct mt76x02_dev*,int,int) ; 
 int /*<<< orphan*/  mt76_set (struct mt76x02_dev*,int,int) ; 
 int /*<<< orphan*/  mt76x2_power_on_rf_patch (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
mt76x2_power_on_rf(struct mt76x02_dev *dev, int unit)
{
	int shift = unit ? 8 : 0;

	/* Enable RF BG */
	mt76_set(dev, 0x10130, BIT(0) << shift);
	udelay(10);

	/* Enable RFDIG LDO/AFE/ABB/ADDA */
	mt76_set(dev, 0x10130, (BIT(1) | BIT(3) | BIT(4) | BIT(5)) << shift);
	udelay(10);

	/* Switch RFDIG power to internal LDO */
	mt76_clear(dev, 0x10130, BIT(2) << shift);
	udelay(10);

	mt76x2_power_on_rf_patch(dev);

	mt76_set(dev, 0x530, 0xf);
}