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
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
mt76x2_power_on_rf_patch(struct mt76x02_dev *dev)
{
	mt76_set(dev, 0x10130, BIT(0) | BIT(16));
	udelay(1);

	mt76_clear(dev, 0x1001c, 0xff);
	mt76_set(dev, 0x1001c, 0x30);

	mt76_wr(dev, 0x10014, 0x484f);
	udelay(1);

	mt76_set(dev, 0x10130, BIT(17));
	udelay(125);

	mt76_clear(dev, 0x10130, BIT(16));
	udelay(50);

	mt76_set(dev, 0x1014c, BIT(19) | BIT(20));
}