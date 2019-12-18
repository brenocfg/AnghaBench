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
typedef  int u32 ;
struct emac_adapter {int irq_mod; int automatic; int single_pause_mode; int /*<<< orphan*/  preamble; int /*<<< orphan*/  rfd_burst; int /*<<< orphan*/  tpd_burst; int /*<<< orphan*/  dmaw_dly_cnt; int /*<<< orphan*/  dmar_dly_cnt; int /*<<< orphan*/  dmaw_block; int /*<<< orphan*/  dmar_block; int /*<<< orphan*/  dma_order; int /*<<< orphan*/  rx_desc_cnt; int /*<<< orphan*/  tx_desc_cnt; int /*<<< orphan*/  rfd_size; int /*<<< orphan*/  tpd_size; int /*<<< orphan*/  rrd_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_DLY_CNT_DEF ; 
 int /*<<< orphan*/  DMAW_DLY_CNT_DEF ; 
 int /*<<< orphan*/  EMAC_DEF_RX_DESCS ; 
 int EMAC_DEF_RX_IRQ_MOD ; 
 int /*<<< orphan*/  EMAC_DEF_TX_DESCS ; 
 int EMAC_DEF_TX_IRQ_MOD ; 
 int /*<<< orphan*/  EMAC_PREAMBLE_DEF ; 
 int /*<<< orphan*/  EMAC_RFD_SIZE ; 
 int /*<<< orphan*/  EMAC_RRD_SIZE ; 
 int /*<<< orphan*/  EMAC_TPD_SIZE ; 
 int IRQ_MODERATOR2_INIT_SHFT ; 
 int IRQ_MODERATOR_INIT_SHFT ; 
 int /*<<< orphan*/  RXQ0_NUM_RFD_PREF_DEF ; 
 int /*<<< orphan*/  TXQ0_NUM_TPD_PREF_DEF ; 
 int /*<<< orphan*/  emac_dma_ord_out ; 
 int /*<<< orphan*/  emac_dma_req_128 ; 
 int /*<<< orphan*/  emac_dma_req_4096 ; 

__attribute__((used)) static void emac_init_adapter(struct emac_adapter *adpt)
{
	u32 reg;

	adpt->rrd_size = EMAC_RRD_SIZE;
	adpt->tpd_size = EMAC_TPD_SIZE;
	adpt->rfd_size = EMAC_RFD_SIZE;

	/* descriptors */
	adpt->tx_desc_cnt = EMAC_DEF_TX_DESCS;
	adpt->rx_desc_cnt = EMAC_DEF_RX_DESCS;

	/* dma */
	adpt->dma_order = emac_dma_ord_out;
	adpt->dmar_block = emac_dma_req_4096;
	adpt->dmaw_block = emac_dma_req_128;
	adpt->dmar_dly_cnt = DMAR_DLY_CNT_DEF;
	adpt->dmaw_dly_cnt = DMAW_DLY_CNT_DEF;
	adpt->tpd_burst = TXQ0_NUM_TPD_PREF_DEF;
	adpt->rfd_burst = RXQ0_NUM_RFD_PREF_DEF;

	/* irq moderator */
	reg = ((EMAC_DEF_RX_IRQ_MOD >> 1) << IRQ_MODERATOR2_INIT_SHFT) |
	      ((EMAC_DEF_TX_IRQ_MOD >> 1) << IRQ_MODERATOR_INIT_SHFT);
	adpt->irq_mod = reg;

	/* others */
	adpt->preamble = EMAC_PREAMBLE_DEF;

	/* default to automatic flow control */
	adpt->automatic = true;

	/* Disable single-pause-frame mode by default */
	adpt->single_pause_mode = false;
}