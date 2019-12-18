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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct mt76x02_dev {TYPE_1__ mt76; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_MAC_STATUS ; 
 int /*<<< orphan*/  MT_MAC_STATUS_RX ; 
 int /*<<< orphan*/  MT_MAC_STATUS_TX ; 
 int /*<<< orphan*/  MT_MAC_SYS_CTRL ; 
 int MT_MAC_SYS_CTRL_ENABLE_RX ; 
 int MT_MAC_SYS_CTRL_ENABLE_TX ; 
 int MT_RXQ_STA ; 
 int /*<<< orphan*/  MT_TXOP_CTRL_CFG ; 
 int MT_TXOP_ED_CCA_EN ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mt76_clear (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_poll (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mt76_rr (struct mt76x02_dev*,int) ; 

void mt76x0_mac_stop(struct mt76x02_dev *dev)
{
	int i = 200, ok = 0;

	mt76_clear(dev, MT_TXOP_CTRL_CFG, MT_TXOP_ED_CCA_EN);

	/* Page count on TxQ */
	while (i-- && ((mt76_rr(dev, 0x0438) & 0xffffffff) ||
		       (mt76_rr(dev, 0x0a30) & 0x000000ff) ||
		       (mt76_rr(dev, 0x0a34) & 0x00ff00ff)))
		msleep(10);

	if (!mt76_poll(dev, MT_MAC_STATUS, MT_MAC_STATUS_TX, 0, 1000))
		dev_warn(dev->mt76.dev, "Warning: MAC TX did not stop!\n");

	mt76_clear(dev, MT_MAC_SYS_CTRL, MT_MAC_SYS_CTRL_ENABLE_RX |
					 MT_MAC_SYS_CTRL_ENABLE_TX);

	/* Page count on RxQ */
	for (i = 0; i < 200; i++) {
		if (!(mt76_rr(dev, MT_RXQ_STA) & 0x00ff0000) &&
		    !mt76_rr(dev, 0x0a30) &&
		    !mt76_rr(dev, 0x0a34)) {
			if (ok++ > 5)
				break;
			continue;
		}
		msleep(1);
	}

	if (!mt76_poll(dev, MT_MAC_STATUS, MT_MAC_STATUS_RX, 0, 1000))
		dev_warn(dev->mt76.dev, "Warning: MAC RX did not stop!\n");
}