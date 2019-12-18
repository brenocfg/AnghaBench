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
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct bnx2 {int flags; int bus_speed_mhz; int* mac_addr; int idle_chk_status_idx; int tx_quick_cons_trip_int; int tx_quick_cons_trip; int rx_quick_cons_trip_int; int rx_quick_cons_trip; int comp_prod_trip_int; int comp_prod_trip; int tx_ticks_int; int tx_ticks; int rx_ticks_int; int rx_ticks; int com_ticks_int; int com_ticks; int cmd_ticks_int; int cmd_ticks; int stats_ticks; int irq_nvecs; void* hc_cmd; TYPE_3__* dev; scalar_t__ stats_blk_mapping; scalar_t__ status_blk_mapping; TYPE_2__* bnx2_napi; int /*<<< orphan*/  status_stats_size; scalar_t__ pcix_cap; int /*<<< orphan*/  pdev; } ;
struct TYPE_6__ {int mtu; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  msi; } ;
struct TYPE_5__ {scalar_t__ last_status_idx; TYPE_1__ status_blk; } ;

/* Variables and functions */
 scalar_t__ BNX2_CHIP (struct bnx2*) ; 
 scalar_t__ BNX2_CHIP_5706 ; 
 scalar_t__ BNX2_CHIP_5709 ; 
 scalar_t__ BNX2_CHIP_ID (struct bnx2*) ; 
 scalar_t__ BNX2_CHIP_ID_5706_A0 ; 
 scalar_t__ BNX2_CHIP_ID_5706_A1 ; 
 scalar_t__ BNX2_CHIP_REV (struct bnx2*) ; 
 scalar_t__ BNX2_CHIP_REV_Ax ; 
 int BNX2_DMA_CONFIG ; 
 int BNX2_DMA_CONFIG_CNTL_BYTE_SWAP ; 
 int BNX2_DMA_CONFIG_CNTL_PING_PONG_DMA ; 
 int BNX2_DMA_CONFIG_CNTL_WORD_SWAP ; 
 int BNX2_DMA_CONFIG_DATA_BYTE_SWAP ; 
 int BNX2_DMA_CONFIG_DATA_WORD_SWAP ; 
 int BNX2_DRV_MSG_CODE_RESET ; 
 int BNX2_DRV_MSG_DATA_WAIT2 ; 
 int BNX2_EMAC_ATTENTION_ENA ; 
 int BNX2_EMAC_ATTENTION_ENA_LINK ; 
 int BNX2_EMAC_BACKOFF_SEED ; 
 int BNX2_EMAC_RX_MTU_SIZE ; 
 int BNX2_EMAC_RX_MTU_SIZE_JUMBO_ENA ; 
 int BNX2_FLAG_BROKEN_STATS ; 
 int BNX2_FLAG_ONE_SHOT_MSI ; 
 int BNX2_FLAG_PCIX ; 
 int BNX2_FLAG_USING_MSIX ; 
 int /*<<< orphan*/  BNX2_FW_RX_LOW_LATENCY ; 
 int BNX2_HC_ATTN_BITS_ENABLE ; 
 int BNX2_HC_CMD_TICKS ; 
 int BNX2_HC_COMMAND ; 
 int BNX2_HC_COMMAND_CLR_STAT_NOW ; 
 int BNX2_HC_COMP_PROD_TRIP ; 
 int BNX2_HC_COM_TICKS ; 
 int BNX2_HC_CONFIG ; 
 int BNX2_HC_CONFIG_COLLECT_STATS ; 
 int BNX2_HC_CONFIG_ONE_SHOT ; 
 int BNX2_HC_CONFIG_RX_TMR_MODE ; 
 int BNX2_HC_CONFIG_SB_ADDR_INC_128B ; 
 int BNX2_HC_CONFIG_TX_TMR_MODE ; 
 int BNX2_HC_CONFIG_USE_INT_PARAM ; 
 int BNX2_HC_MSIX_BIT_VECTOR ; 
 int BNX2_HC_MSIX_BIT_VECTOR_VAL ; 
 int BNX2_HC_RX_QUICK_CONS_TRIP ; 
 int BNX2_HC_RX_QUICK_CONS_TRIP_OFF ; 
 int BNX2_HC_RX_TICKS ; 
 int BNX2_HC_RX_TICKS_OFF ; 
 int BNX2_HC_SB_CONFIG_1 ; 
 int BNX2_HC_SB_CONFIG_1_ONE_SHOT ; 
 int BNX2_HC_SB_CONFIG_1_RX_TMR_MODE ; 
 int BNX2_HC_SB_CONFIG_1_TX_TMR_MODE ; 
 int BNX2_HC_SB_CONFIG_SIZE ; 
 int BNX2_HC_STATISTICS_ADDR_H ; 
 int BNX2_HC_STATISTICS_ADDR_L ; 
 int BNX2_HC_STATS_TICKS ; 
 int BNX2_HC_STATUS_ADDR_H ; 
 int BNX2_HC_STATUS_ADDR_L ; 
 int BNX2_HC_STAT_COLLECT_TICKS ; 
 int BNX2_HC_TX_QUICK_CONS_TRIP ; 
 int BNX2_HC_TX_QUICK_CONS_TRIP_OFF ; 
 int BNX2_HC_TX_TICKS ; 
 int BNX2_HC_TX_TICKS_OFF ; 
 int BNX2_MAX_MSIX_VEC ; 
 int BNX2_MISC_ENABLE_DEFAULT ; 
 int BNX2_MISC_ENABLE_SET_BITS ; 
 int BNX2_MISC_ENABLE_SET_BITS_HOST_COALESCE_ENABLE ; 
 int BNX2_MISC_ENABLE_STATUS_BITS_CONTEXT_ENABLE ; 
 int BNX2_MISC_ENABLE_STATUS_BITS_RX_V2P_ENABLE ; 
 int BNX2_MISC_NEW_CORE_CTL ; 
 int BNX2_MISC_NEW_CORE_CTL_DMA_ENABLE ; 
 int BNX2_MQ_CONFIG ; 
 int BNX2_MQ_CONFIG_BIN_MQ_MODE ; 
 int BNX2_MQ_CONFIG_HALT_DIS ; 
 int BNX2_MQ_CONFIG_KNL_BYP_BLK_SIZE ; 
 int BNX2_MQ_CONFIG_KNL_BYP_BLK_SIZE_256 ; 
 int BNX2_MQ_KNL_BYP_WIND_START ; 
 int BNX2_MQ_KNL_WIND_END ; 
 int BNX2_PAGE_BITS ; 
 int BNX2_PCICFG_INT_ACK_CMD ; 
 int BNX2_PCICFG_INT_ACK_CMD_MASK_INT ; 
 int /*<<< orphan*/  BNX2_RBUF_CONFIG ; 
 int /*<<< orphan*/  BNX2_RBUF_CONFIG2 ; 
 int BNX2_RBUF_CONFIG2_VAL (int) ; 
 int /*<<< orphan*/  BNX2_RBUF_CONFIG3 ; 
 int BNX2_RBUF_CONFIG3_VAL (int) ; 
 int BNX2_RBUF_CONFIG_VAL (int) ; 
 void* BNX2_RD (struct bnx2*,int) ; 
 int BNX2_RV2P_CONFIG ; 
 int BNX2_TBDR_CONFIG ; 
 int BNX2_TBDR_CONFIG_PAGE_SIZE ; 
 int BNX2_TDMA_CONFIG ; 
 int BNX2_TDMA_CONFIG_ONE_DMA ; 
 int /*<<< orphan*/  BNX2_WR (struct bnx2*,int,int) ; 
 int DMA_READ_CHANS ; 
 int DMA_WRITE_CHANS ; 
 int ETH_DATA_LEN ; 
 int ETH_FCS_LEN ; 
 int ETH_HLEN ; 
 int MAX_CID_CNT ; 
 int MAX_ETHERNET_PACKET_SIZE ; 
 int MB_KERNEL_CTX_SIZE ; 
 scalar_t__ PCI_X_CMD ; 
 int PCI_X_CMD_ERO ; 
 int STATUS_ATTN_EVENTS ; 
 int bnx2_fw_sync (struct bnx2*,int,int,int /*<<< orphan*/ ) ; 
 int bnx2_init_5709_context (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_init_context (struct bnx2*) ; 
 int bnx2_init_cpus (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_init_nvram (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_reg_wr_ind (struct bnx2*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2_set_mac_addr (struct bnx2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2_set_rx_mode (TYPE_3__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
bnx2_init_chip(struct bnx2 *bp)
{
	u32 val, mtu;
	int rc, i;

	/* Make sure the interrupt is not active. */
	BNX2_WR(bp, BNX2_PCICFG_INT_ACK_CMD, BNX2_PCICFG_INT_ACK_CMD_MASK_INT);

	val = BNX2_DMA_CONFIG_DATA_BYTE_SWAP |
	      BNX2_DMA_CONFIG_DATA_WORD_SWAP |
#ifdef __BIG_ENDIAN
	      BNX2_DMA_CONFIG_CNTL_BYTE_SWAP |
#endif
	      BNX2_DMA_CONFIG_CNTL_WORD_SWAP |
	      DMA_READ_CHANS << 12 |
	      DMA_WRITE_CHANS << 16;

	val |= (0x2 << 20) | (1 << 11);

	if ((bp->flags & BNX2_FLAG_PCIX) && (bp->bus_speed_mhz == 133))
		val |= (1 << 23);

	if ((BNX2_CHIP(bp) == BNX2_CHIP_5706) &&
	    (BNX2_CHIP_ID(bp) != BNX2_CHIP_ID_5706_A0) &&
	    !(bp->flags & BNX2_FLAG_PCIX))
		val |= BNX2_DMA_CONFIG_CNTL_PING_PONG_DMA;

	BNX2_WR(bp, BNX2_DMA_CONFIG, val);

	if (BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5706_A0) {
		val = BNX2_RD(bp, BNX2_TDMA_CONFIG);
		val |= BNX2_TDMA_CONFIG_ONE_DMA;
		BNX2_WR(bp, BNX2_TDMA_CONFIG, val);
	}

	if (bp->flags & BNX2_FLAG_PCIX) {
		u16 val16;

		pci_read_config_word(bp->pdev, bp->pcix_cap + PCI_X_CMD,
				     &val16);
		pci_write_config_word(bp->pdev, bp->pcix_cap + PCI_X_CMD,
				      val16 & ~PCI_X_CMD_ERO);
	}

	BNX2_WR(bp, BNX2_MISC_ENABLE_SET_BITS,
		BNX2_MISC_ENABLE_SET_BITS_HOST_COALESCE_ENABLE |
		BNX2_MISC_ENABLE_STATUS_BITS_RX_V2P_ENABLE |
		BNX2_MISC_ENABLE_STATUS_BITS_CONTEXT_ENABLE);

	/* Initialize context mapping and zero out the quick contexts.  The
	 * context block must have already been enabled. */
	if (BNX2_CHIP(bp) == BNX2_CHIP_5709) {
		rc = bnx2_init_5709_context(bp);
		if (rc)
			return rc;
	} else
		bnx2_init_context(bp);

	if ((rc = bnx2_init_cpus(bp)) != 0)
		return rc;

	bnx2_init_nvram(bp);

	bnx2_set_mac_addr(bp, bp->dev->dev_addr, 0);

	val = BNX2_RD(bp, BNX2_MQ_CONFIG);
	val &= ~BNX2_MQ_CONFIG_KNL_BYP_BLK_SIZE;
	val |= BNX2_MQ_CONFIG_KNL_BYP_BLK_SIZE_256;
	if (BNX2_CHIP(bp) == BNX2_CHIP_5709) {
		val |= BNX2_MQ_CONFIG_BIN_MQ_MODE;
		if (BNX2_CHIP_REV(bp) == BNX2_CHIP_REV_Ax)
			val |= BNX2_MQ_CONFIG_HALT_DIS;
	}

	BNX2_WR(bp, BNX2_MQ_CONFIG, val);

	val = 0x10000 + (MAX_CID_CNT * MB_KERNEL_CTX_SIZE);
	BNX2_WR(bp, BNX2_MQ_KNL_BYP_WIND_START, val);
	BNX2_WR(bp, BNX2_MQ_KNL_WIND_END, val);

	val = (BNX2_PAGE_BITS - 8) << 24;
	BNX2_WR(bp, BNX2_RV2P_CONFIG, val);

	/* Configure page size. */
	val = BNX2_RD(bp, BNX2_TBDR_CONFIG);
	val &= ~BNX2_TBDR_CONFIG_PAGE_SIZE;
	val |= (BNX2_PAGE_BITS - 8) << 24 | 0x40;
	BNX2_WR(bp, BNX2_TBDR_CONFIG, val);

	val = bp->mac_addr[0] +
	      (bp->mac_addr[1] << 8) +
	      (bp->mac_addr[2] << 16) +
	      bp->mac_addr[3] +
	      (bp->mac_addr[4] << 8) +
	      (bp->mac_addr[5] << 16);
	BNX2_WR(bp, BNX2_EMAC_BACKOFF_SEED, val);

	/* Program the MTU.  Also include 4 bytes for CRC32. */
	mtu = bp->dev->mtu;
	val = mtu + ETH_HLEN + ETH_FCS_LEN;
	if (val > (MAX_ETHERNET_PACKET_SIZE + ETH_HLEN + 4))
		val |= BNX2_EMAC_RX_MTU_SIZE_JUMBO_ENA;
	BNX2_WR(bp, BNX2_EMAC_RX_MTU_SIZE, val);

	if (mtu < ETH_DATA_LEN)
		mtu = ETH_DATA_LEN;

	bnx2_reg_wr_ind(bp, BNX2_RBUF_CONFIG, BNX2_RBUF_CONFIG_VAL(mtu));
	bnx2_reg_wr_ind(bp, BNX2_RBUF_CONFIG2, BNX2_RBUF_CONFIG2_VAL(mtu));
	bnx2_reg_wr_ind(bp, BNX2_RBUF_CONFIG3, BNX2_RBUF_CONFIG3_VAL(mtu));

	memset(bp->bnx2_napi[0].status_blk.msi, 0, bp->status_stats_size);
	for (i = 0; i < BNX2_MAX_MSIX_VEC; i++)
		bp->bnx2_napi[i].last_status_idx = 0;

	bp->idle_chk_status_idx = 0xffff;

	/* Set up how to generate a link change interrupt. */
	BNX2_WR(bp, BNX2_EMAC_ATTENTION_ENA, BNX2_EMAC_ATTENTION_ENA_LINK);

	BNX2_WR(bp, BNX2_HC_STATUS_ADDR_L,
		(u64) bp->status_blk_mapping & 0xffffffff);
	BNX2_WR(bp, BNX2_HC_STATUS_ADDR_H, (u64) bp->status_blk_mapping >> 32);

	BNX2_WR(bp, BNX2_HC_STATISTICS_ADDR_L,
		(u64) bp->stats_blk_mapping & 0xffffffff);
	BNX2_WR(bp, BNX2_HC_STATISTICS_ADDR_H,
		(u64) bp->stats_blk_mapping >> 32);

	BNX2_WR(bp, BNX2_HC_TX_QUICK_CONS_TRIP,
		(bp->tx_quick_cons_trip_int << 16) | bp->tx_quick_cons_trip);

	BNX2_WR(bp, BNX2_HC_RX_QUICK_CONS_TRIP,
		(bp->rx_quick_cons_trip_int << 16) | bp->rx_quick_cons_trip);

	BNX2_WR(bp, BNX2_HC_COMP_PROD_TRIP,
		(bp->comp_prod_trip_int << 16) | bp->comp_prod_trip);

	BNX2_WR(bp, BNX2_HC_TX_TICKS, (bp->tx_ticks_int << 16) | bp->tx_ticks);

	BNX2_WR(bp, BNX2_HC_RX_TICKS, (bp->rx_ticks_int << 16) | bp->rx_ticks);

	BNX2_WR(bp, BNX2_HC_COM_TICKS,
		(bp->com_ticks_int << 16) | bp->com_ticks);

	BNX2_WR(bp, BNX2_HC_CMD_TICKS,
		(bp->cmd_ticks_int << 16) | bp->cmd_ticks);

	if (bp->flags & BNX2_FLAG_BROKEN_STATS)
		BNX2_WR(bp, BNX2_HC_STATS_TICKS, 0);
	else
		BNX2_WR(bp, BNX2_HC_STATS_TICKS, bp->stats_ticks);
	BNX2_WR(bp, BNX2_HC_STAT_COLLECT_TICKS, 0xbb8);  /* 3ms */

	if (BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5706_A1)
		val = BNX2_HC_CONFIG_COLLECT_STATS;
	else {
		val = BNX2_HC_CONFIG_RX_TMR_MODE | BNX2_HC_CONFIG_TX_TMR_MODE |
		      BNX2_HC_CONFIG_COLLECT_STATS;
	}

	if (bp->flags & BNX2_FLAG_USING_MSIX) {
		BNX2_WR(bp, BNX2_HC_MSIX_BIT_VECTOR,
			BNX2_HC_MSIX_BIT_VECTOR_VAL);

		val |= BNX2_HC_CONFIG_SB_ADDR_INC_128B;
	}

	if (bp->flags & BNX2_FLAG_ONE_SHOT_MSI)
		val |= BNX2_HC_CONFIG_ONE_SHOT | BNX2_HC_CONFIG_USE_INT_PARAM;

	BNX2_WR(bp, BNX2_HC_CONFIG, val);

	if (bp->rx_ticks < 25)
		bnx2_reg_wr_ind(bp, BNX2_FW_RX_LOW_LATENCY, 1);
	else
		bnx2_reg_wr_ind(bp, BNX2_FW_RX_LOW_LATENCY, 0);

	for (i = 1; i < bp->irq_nvecs; i++) {
		u32 base = ((i - 1) * BNX2_HC_SB_CONFIG_SIZE) +
			   BNX2_HC_SB_CONFIG_1;

		BNX2_WR(bp, base,
			BNX2_HC_SB_CONFIG_1_TX_TMR_MODE |
			BNX2_HC_SB_CONFIG_1_RX_TMR_MODE |
			BNX2_HC_SB_CONFIG_1_ONE_SHOT);

		BNX2_WR(bp, base + BNX2_HC_TX_QUICK_CONS_TRIP_OFF,
			(bp->tx_quick_cons_trip_int << 16) |
			 bp->tx_quick_cons_trip);

		BNX2_WR(bp, base + BNX2_HC_TX_TICKS_OFF,
			(bp->tx_ticks_int << 16) | bp->tx_ticks);

		BNX2_WR(bp, base + BNX2_HC_RX_QUICK_CONS_TRIP_OFF,
			(bp->rx_quick_cons_trip_int << 16) |
			bp->rx_quick_cons_trip);

		BNX2_WR(bp, base + BNX2_HC_RX_TICKS_OFF,
			(bp->rx_ticks_int << 16) | bp->rx_ticks);
	}

	/* Clear internal stats counters. */
	BNX2_WR(bp, BNX2_HC_COMMAND, BNX2_HC_COMMAND_CLR_STAT_NOW);

	BNX2_WR(bp, BNX2_HC_ATTN_BITS_ENABLE, STATUS_ATTN_EVENTS);

	/* Initialize the receive filter. */
	bnx2_set_rx_mode(bp->dev);

	if (BNX2_CHIP(bp) == BNX2_CHIP_5709) {
		val = BNX2_RD(bp, BNX2_MISC_NEW_CORE_CTL);
		val |= BNX2_MISC_NEW_CORE_CTL_DMA_ENABLE;
		BNX2_WR(bp, BNX2_MISC_NEW_CORE_CTL, val);
	}
	rc = bnx2_fw_sync(bp, BNX2_DRV_MSG_DATA_WAIT2 | BNX2_DRV_MSG_CODE_RESET,
			  1, 0);

	BNX2_WR(bp, BNX2_MISC_ENABLE_SET_BITS, BNX2_MISC_ENABLE_DEFAULT);
	BNX2_RD(bp, BNX2_MISC_ENABLE_SET_BITS);

	udelay(20);

	bp->hc_cmd = BNX2_RD(bp, BNX2_HC_COMMAND);

	return rc;
}