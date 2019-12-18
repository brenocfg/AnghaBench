#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  consume_shift; int /*<<< orphan*/  consume_mask; int /*<<< orphan*/  consume_reg; int /*<<< orphan*/  produce_shift; int /*<<< orphan*/  produce_mask; int /*<<< orphan*/  produce_reg; } ;
struct TYPE_5__ {int mask; } ;
struct TYPE_4__ {int intr; TYPE_2__* irq; int /*<<< orphan*/  consume_shift; int /*<<< orphan*/  consume_mask; int /*<<< orphan*/  consume_reg; int /*<<< orphan*/  process_shft; int /*<<< orphan*/  process_mask; void* process_reg; int /*<<< orphan*/  produce_shift; int /*<<< orphan*/  produce_mask; void* produce_reg; int /*<<< orphan*/  netdev; } ;
struct emac_adapter {TYPE_3__ tx_q; TYPE_2__ irq; TYPE_1__ rx_q; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 void* EMAC_MAILBOX_0 ; 
 int /*<<< orphan*/  EMAC_MAILBOX_15 ; 
 int /*<<< orphan*/  EMAC_MAILBOX_2 ; 
 int /*<<< orphan*/  EMAC_MAILBOX_3 ; 
 int ISR_RX_PKT ; 
 int /*<<< orphan*/  NTPD_CONS_IDX_BMSK ; 
 int /*<<< orphan*/  NTPD_CONS_IDX_SHFT ; 
 int /*<<< orphan*/  NTPD_PROD_IDX_BMSK ; 
 int /*<<< orphan*/  NTPD_PROD_IDX_SHFT ; 
 int /*<<< orphan*/  RFD0_CONS_IDX_BMSK ; 
 int /*<<< orphan*/  RFD0_CONS_IDX_SHFT ; 
 int /*<<< orphan*/  RFD0_PROC_IDX_BMSK ; 
 int /*<<< orphan*/  RFD0_PROC_IDX_SHFT ; 
 int /*<<< orphan*/  RFD0_PROD_IDX_BMSK ; 
 int /*<<< orphan*/  RFD0_PROD_IDX_SHFT ; 

void emac_mac_rx_tx_ring_init_all(struct platform_device *pdev,
				  struct emac_adapter *adpt)
{
	adpt->rx_q.netdev = adpt->netdev;

	adpt->rx_q.produce_reg  = EMAC_MAILBOX_0;
	adpt->rx_q.produce_mask = RFD0_PROD_IDX_BMSK;
	adpt->rx_q.produce_shift = RFD0_PROD_IDX_SHFT;

	adpt->rx_q.process_reg  = EMAC_MAILBOX_0;
	adpt->rx_q.process_mask = RFD0_PROC_IDX_BMSK;
	adpt->rx_q.process_shft = RFD0_PROC_IDX_SHFT;

	adpt->rx_q.consume_reg  = EMAC_MAILBOX_3;
	adpt->rx_q.consume_mask = RFD0_CONS_IDX_BMSK;
	adpt->rx_q.consume_shift = RFD0_CONS_IDX_SHFT;

	adpt->rx_q.irq          = &adpt->irq;
	adpt->rx_q.intr         = adpt->irq.mask & ISR_RX_PKT;

	adpt->tx_q.produce_reg  = EMAC_MAILBOX_15;
	adpt->tx_q.produce_mask = NTPD_PROD_IDX_BMSK;
	adpt->tx_q.produce_shift = NTPD_PROD_IDX_SHFT;

	adpt->tx_q.consume_reg  = EMAC_MAILBOX_2;
	adpt->tx_q.consume_mask = NTPD_CONS_IDX_BMSK;
	adpt->tx_q.consume_shift = NTPD_CONS_IDX_SHFT;
}