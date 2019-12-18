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
 int /*<<< orphan*/  MT_RX_STAT_0 ; 
 int /*<<< orphan*/  MT_RX_STAT_1 ; 
 int /*<<< orphan*/  MT_RX_STAT_2 ; 
 int /*<<< orphan*/  MT_TX_STA_0 ; 
 int /*<<< orphan*/  MT_TX_STA_1 ; 
 int /*<<< orphan*/  MT_TX_STA_2 ; 
 int /*<<< orphan*/  mt76_rr (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mt76x0_reset_counters(struct mt76x02_dev *dev)
{
	mt76_rr(dev, MT_RX_STAT_0);
	mt76_rr(dev, MT_RX_STAT_1);
	mt76_rr(dev, MT_RX_STAT_2);
	mt76_rr(dev, MT_TX_STA_0);
	mt76_rr(dev, MT_TX_STA_1);
	mt76_rr(dev, MT_TX_STA_2);
}