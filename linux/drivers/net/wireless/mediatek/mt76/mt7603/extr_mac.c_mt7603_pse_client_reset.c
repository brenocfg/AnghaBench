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
typedef  int /*<<< orphan*/  u32 ;
struct mt7603_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ MT_CLIENT_BASE_PHYS_ADDR ; 
 scalar_t__ MT_CLIENT_RESET_TX ; 
 int MT_CLIENT_RESET_TX_R_E_1 ; 
 int MT_CLIENT_RESET_TX_R_E_1_S ; 
 int MT_CLIENT_RESET_TX_R_E_2 ; 
 int MT_CLIENT_RESET_TX_R_E_2_S ; 
 int /*<<< orphan*/  MT_WPDMA_GLO_CFG ; 
 int MT_WPDMA_GLO_CFG_SW_RESET ; 
 int /*<<< orphan*/  mt7603_reg_map (struct mt7603_dev*,scalar_t__) ; 
 int /*<<< orphan*/  mt76_clear (struct mt7603_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_poll_msec (struct mt7603_dev*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  mt76_set (struct mt7603_dev*,int /*<<< orphan*/ ,int) ; 

void mt7603_pse_client_reset(struct mt7603_dev *dev)
{
	u32 addr;

	addr = mt7603_reg_map(dev, MT_CLIENT_BASE_PHYS_ADDR +
				   MT_CLIENT_RESET_TX);

	/* Clear previous reset state */
	mt76_clear(dev, addr,
		   MT_CLIENT_RESET_TX_R_E_1 |
		   MT_CLIENT_RESET_TX_R_E_2 |
		   MT_CLIENT_RESET_TX_R_E_1_S |
		   MT_CLIENT_RESET_TX_R_E_2_S);

	/* Start PSE client TX abort */
	mt76_set(dev, addr, MT_CLIENT_RESET_TX_R_E_1);
	mt76_poll_msec(dev, addr, MT_CLIENT_RESET_TX_R_E_1_S,
		       MT_CLIENT_RESET_TX_R_E_1_S, 500);

	mt76_set(dev, addr, MT_CLIENT_RESET_TX_R_E_2);
	mt76_set(dev, MT_WPDMA_GLO_CFG, MT_WPDMA_GLO_CFG_SW_RESET);

	/* Wait for PSE client to clear TX FIFO */
	mt76_poll_msec(dev, addr, MT_CLIENT_RESET_TX_R_E_2_S,
		       MT_CLIENT_RESET_TX_R_E_2_S, 500);

	/* Clear PSE client TX abort state */
	mt76_clear(dev, addr,
		   MT_CLIENT_RESET_TX_R_E_1 |
		   MT_CLIENT_RESET_TX_R_E_2);
}