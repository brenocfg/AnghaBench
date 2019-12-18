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
struct TYPE_2__ {int antenna_mask; } ;
struct mt7603_dev {void* agc3; void* agc0; TYPE_1__ mt76; } ;

/* Variables and functions */
 int FIELD_PREP (int,int) ; 
 int /*<<< orphan*/  MT_AGC (int) ; 
 int /*<<< orphan*/  MT_TMAC_TCR ; 
 int /*<<< orphan*/  MT_TMAC_TCR_TX_STREAMS ; 
 int /*<<< orphan*/  MT_WF_RMAC_RMCR ; 
 int MT_WF_RMAC_RMCR_RX_STREAMS ; 
 int MT_WF_RMAC_RMCR_SMPS_MODE ; 
 int hweight8 (int) ; 
 int /*<<< orphan*/  mt76_rmw (struct mt7603_dev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mt76_rmw_field (struct mt7603_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* mt76_rr (struct mt7603_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mt7603_phy_init(struct mt7603_dev *dev)
{
	int rx_chains = dev->mt76.antenna_mask;
	int tx_chains = hweight8(rx_chains) - 1;

	mt76_rmw(dev, MT_WF_RMAC_RMCR,
		 (MT_WF_RMAC_RMCR_SMPS_MODE |
		  MT_WF_RMAC_RMCR_RX_STREAMS),
		 (FIELD_PREP(MT_WF_RMAC_RMCR_SMPS_MODE, 3) |
		  FIELD_PREP(MT_WF_RMAC_RMCR_RX_STREAMS, rx_chains)));

	mt76_rmw_field(dev, MT_TMAC_TCR, MT_TMAC_TCR_TX_STREAMS,
		       tx_chains);

	dev->agc0 = mt76_rr(dev, MT_AGC(0));
	dev->agc3 = mt76_rr(dev, MT_AGC(3));
}