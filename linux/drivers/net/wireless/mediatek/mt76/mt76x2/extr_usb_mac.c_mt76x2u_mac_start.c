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
struct TYPE_2__ {int rxfilter; } ;
struct mt76x02_dev {TYPE_1__ mt76; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_MAC_SYS_CTRL ; 
 int MT_MAC_SYS_CTRL_ENABLE_RX ; 
 int MT_MAC_SYS_CTRL_ENABLE_TX ; 
 int /*<<< orphan*/  MT_RX_FILTR_CFG ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76x02_wait_for_wpdma (TYPE_1__*,int) ; 
 int /*<<< orphan*/  mt76x2u_mac_reset_counters (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int mt76x2u_mac_start(struct mt76x02_dev *dev)
{
	mt76x2u_mac_reset_counters(dev);

	mt76_wr(dev, MT_MAC_SYS_CTRL, MT_MAC_SYS_CTRL_ENABLE_TX);
	mt76x02_wait_for_wpdma(&dev->mt76, 1000);
	usleep_range(50, 100);

	mt76_wr(dev, MT_RX_FILTR_CFG, dev->mt76.rxfilter);

	mt76_wr(dev, MT_MAC_SYS_CTRL,
		MT_MAC_SYS_CTRL_ENABLE_TX |
		MT_MAC_SYS_CTRL_ENABLE_RX);

	return 0;
}