#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * ofdm; } ;
struct TYPE_4__ {TYPE_1__ rate_power; } ;
struct mt76x02_dev {TYPE_2__ mt76; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 int /*<<< orphan*/  MT_PROT_AUTO_TX_CFG ; 
 int /*<<< orphan*/  MT_PROT_AUTO_TX_CFG_AUTO_PADJ ; 
 int /*<<< orphan*/  MT_PROT_AUTO_TX_CFG_PROT_PADJ ; 
 int /*<<< orphan*/  mt76_rmw_field (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x02_tx_get_txpwr_adj (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mt76x02_tx_set_txpwr_auto(struct mt76x02_dev *dev, s8 txpwr)
{
	s8 txpwr_adj;

	txpwr_adj = mt76x02_tx_get_txpwr_adj(dev, txpwr,
					     dev->mt76.rate_power.ofdm[4]);
	mt76_rmw_field(dev, MT_PROT_AUTO_TX_CFG,
		       MT_PROT_AUTO_TX_CFG_PROT_PADJ, txpwr_adj);
	mt76_rmw_field(dev, MT_PROT_AUTO_TX_CFG,
		       MT_PROT_AUTO_TX_CFG_AUTO_PADJ, txpwr_adj);
}