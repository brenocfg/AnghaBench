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
struct mt76x02_dev {int /*<<< orphan*/  aggr_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_TX_AGG_CNT (int) ; 
 int /*<<< orphan*/  MT_TX_STAT_FIFO ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_rr (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x02_mac_start (struct mt76x02_dev*) ; 

int mt76x2_mac_start(struct mt76x02_dev *dev)
{
	int i;

	for (i = 0; i < 16; i++)
		mt76_rr(dev, MT_TX_AGG_CNT(i));

	for (i = 0; i < 16; i++)
		mt76_rr(dev, MT_TX_STAT_FIFO);

	memset(dev->aggr_stats, 0, sizeof(dev->aggr_stats));
	mt76x02_mac_start(dev);

	return 0;
}