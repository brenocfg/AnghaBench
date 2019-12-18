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
struct TYPE_2__ {int chainmask; } ;
struct mt76x02_dev {TYPE_1__ mt76; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_BBP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TXBE ; 
 int /*<<< orphan*/  mt76_clear (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_set (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 

void mt76x02_phy_set_txdac(struct mt76x02_dev *dev)
{
	int txpath;

	txpath = (dev->mt76.chainmask >> 8) & 0xf;
	switch (txpath) {
	case 2:
		mt76_set(dev, MT_BBP(TXBE, 5), 0x3);
		break;
	default:
		mt76_clear(dev, MT_BBP(TXBE, 5), 0x3);
		break;
	}
}