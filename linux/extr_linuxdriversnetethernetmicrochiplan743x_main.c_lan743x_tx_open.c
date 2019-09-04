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
typedef  int u32 ;
struct lan743x_tx {int ring_size; int vector_flags; int /*<<< orphan*/  channel_number; int /*<<< orphan*/  napi; scalar_t__ last_tail; void* last_head; int /*<<< orphan*/  head_dma_ptr; int /*<<< orphan*/  ring_dma_ptr; struct lan743x_adapter* adapter; } ;
struct TYPE_2__ {int flags; } ;
struct lan743x_adapter {int /*<<< orphan*/  netdev; TYPE_1__ csr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAC_CMD ; 
 int DMAC_CMD_START_T_ (int /*<<< orphan*/ ) ; 
 int DMAC_CMD_TX_SWR_ (int /*<<< orphan*/ ) ; 
 int DMAC_INT_BIT_TX_IOC_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMAC_INT_EN_SET ; 
 int DMA_ADDR_HIGH32 (int /*<<< orphan*/ ) ; 
 int DMA_ADDR_LOW32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FCT_TX_CTL ; 
 int FCT_TX_CTL_EN_ (int /*<<< orphan*/ ) ; 
 int FCT_TX_CTL_RESET_ (int /*<<< orphan*/ ) ; 
 int INT_BIT_DMA_TX_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT_EN_SET ; 
 int LAN743X_CSR_FLAG_IS_A0 ; 
 int LAN743X_VECTOR_FLAG_SOURCE_ENABLE_AUTO_CLEAR ; 
 int LAN743X_VECTOR_FLAG_SOURCE_ENABLE_AUTO_SET ; 
 int LAN743X_VECTOR_FLAG_SOURCE_ENABLE_R2C ; 
 int LAN743X_VECTOR_FLAG_SOURCE_STATUS_AUTO_CLEAR ; 
 int LAN743X_VECTOR_FLAG_SOURCE_STATUS_R2C ; 
 int /*<<< orphan*/  TX_BASE_ADDRH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TX_BASE_ADDRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TX_CFG_A (int /*<<< orphan*/ ) ; 
 int TX_CFG_A_TX_HP_WB_EN_ ; 
 int TX_CFG_A_TX_HP_WB_ON_INT_TMR_ ; 
 int TX_CFG_A_TX_HP_WB_THRES_SET_ (int) ; 
 int TX_CFG_A_TX_PF_PRI_THRES_SET_ (int) ; 
 int TX_CFG_A_TX_PF_THRES_SET_ (int) ; 
 int TX_CFG_A_TX_TMR_HPWB_SEL_IOC_ ; 
 int /*<<< orphan*/  TX_CFG_B (int /*<<< orphan*/ ) ; 
 int TX_CFG_B_TDMABL_512_ ; 
 int TX_CFG_B_TX_RING_LEN_MASK_ ; 
 int /*<<< orphan*/  TX_CFG_C (int /*<<< orphan*/ ) ; 
 int TX_CFG_C_TX_DMA_INT_STS_AUTO_CLR_ ; 
 int TX_CFG_C_TX_INT_EN_R2C_ ; 
 int TX_CFG_C_TX_INT_STS_R2C_MODE_MASK_ ; 
 int TX_CFG_C_TX_TOP_INT_EN_AUTO_CLR_ ; 
 int /*<<< orphan*/  TX_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TX_HEAD_WRITEBACK_ADDRH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TX_HEAD_WRITEBACK_ADDRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TX_TAIL (int /*<<< orphan*/ ) ; 
 void* lan743x_csr_read (struct lan743x_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lan743x_csr_wait_for_bit (struct lan743x_adapter*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  lan743x_csr_write (struct lan743x_adapter*,int /*<<< orphan*/ ,int) ; 
 int lan743x_intr_get_vector_flags (struct lan743x_adapter*,int) ; 
 int /*<<< orphan*/  lan743x_tx_napi_poll ; 
 int lan743x_tx_ring_init (struct lan743x_tx*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_tx_napi_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lan743x_tx_open(struct lan743x_tx *tx)
{
	struct lan743x_adapter *adapter = NULL;
	u32 data = 0;
	int ret;

	adapter = tx->adapter;
	ret = lan743x_tx_ring_init(tx);
	if (ret)
		return ret;

	/* initialize fifo */
	lan743x_csr_write(adapter, FCT_TX_CTL,
			  FCT_TX_CTL_RESET_(tx->channel_number));
	lan743x_csr_wait_for_bit(adapter, FCT_TX_CTL,
				 FCT_TX_CTL_RESET_(tx->channel_number),
				 0, 1000, 20000, 100);

	/* enable fifo */
	lan743x_csr_write(adapter, FCT_TX_CTL,
			  FCT_TX_CTL_EN_(tx->channel_number));

	/* reset tx channel */
	lan743x_csr_write(adapter, DMAC_CMD,
			  DMAC_CMD_TX_SWR_(tx->channel_number));
	lan743x_csr_wait_for_bit(adapter, DMAC_CMD,
				 DMAC_CMD_TX_SWR_(tx->channel_number),
				 0, 1000, 20000, 100);

	/* Write TX_BASE_ADDR */
	lan743x_csr_write(adapter,
			  TX_BASE_ADDRH(tx->channel_number),
			  DMA_ADDR_HIGH32(tx->ring_dma_ptr));
	lan743x_csr_write(adapter,
			  TX_BASE_ADDRL(tx->channel_number),
			  DMA_ADDR_LOW32(tx->ring_dma_ptr));

	/* Write TX_CFG_B */
	data = lan743x_csr_read(adapter, TX_CFG_B(tx->channel_number));
	data &= ~TX_CFG_B_TX_RING_LEN_MASK_;
	data |= ((tx->ring_size) & TX_CFG_B_TX_RING_LEN_MASK_);
	if (!(adapter->csr.flags & LAN743X_CSR_FLAG_IS_A0))
		data |= TX_CFG_B_TDMABL_512_;
	lan743x_csr_write(adapter, TX_CFG_B(tx->channel_number), data);

	/* Write TX_CFG_A */
	data = TX_CFG_A_TX_TMR_HPWB_SEL_IOC_ | TX_CFG_A_TX_HP_WB_EN_;
	if (!(adapter->csr.flags & LAN743X_CSR_FLAG_IS_A0)) {
		data |= TX_CFG_A_TX_HP_WB_ON_INT_TMR_;
		data |= TX_CFG_A_TX_PF_THRES_SET_(0x10);
		data |= TX_CFG_A_TX_PF_PRI_THRES_SET_(0x04);
		data |= TX_CFG_A_TX_HP_WB_THRES_SET_(0x07);
	}
	lan743x_csr_write(adapter, TX_CFG_A(tx->channel_number), data);

	/* Write TX_HEAD_WRITEBACK_ADDR */
	lan743x_csr_write(adapter,
			  TX_HEAD_WRITEBACK_ADDRH(tx->channel_number),
			  DMA_ADDR_HIGH32(tx->head_dma_ptr));
	lan743x_csr_write(adapter,
			  TX_HEAD_WRITEBACK_ADDRL(tx->channel_number),
			  DMA_ADDR_LOW32(tx->head_dma_ptr));

	/* set last head */
	tx->last_head = lan743x_csr_read(adapter, TX_HEAD(tx->channel_number));

	/* write TX_TAIL */
	tx->last_tail = 0;
	lan743x_csr_write(adapter, TX_TAIL(tx->channel_number),
			  (u32)(tx->last_tail));
	tx->vector_flags = lan743x_intr_get_vector_flags(adapter,
							 INT_BIT_DMA_TX_
							 (tx->channel_number));
	netif_tx_napi_add(adapter->netdev,
			  &tx->napi, lan743x_tx_napi_poll,
			  tx->ring_size - 1);
	napi_enable(&tx->napi);

	data = 0;
	if (tx->vector_flags & LAN743X_VECTOR_FLAG_SOURCE_ENABLE_AUTO_CLEAR)
		data |= TX_CFG_C_TX_TOP_INT_EN_AUTO_CLR_;
	if (tx->vector_flags & LAN743X_VECTOR_FLAG_SOURCE_STATUS_AUTO_CLEAR)
		data |= TX_CFG_C_TX_DMA_INT_STS_AUTO_CLR_;
	if (tx->vector_flags & LAN743X_VECTOR_FLAG_SOURCE_STATUS_R2C)
		data |= TX_CFG_C_TX_INT_STS_R2C_MODE_MASK_;
	if (tx->vector_flags & LAN743X_VECTOR_FLAG_SOURCE_ENABLE_R2C)
		data |= TX_CFG_C_TX_INT_EN_R2C_;
	lan743x_csr_write(adapter, TX_CFG_C(tx->channel_number), data);

	if (!(tx->vector_flags & LAN743X_VECTOR_FLAG_SOURCE_ENABLE_AUTO_SET))
		lan743x_csr_write(adapter, INT_EN_SET,
				  INT_BIT_DMA_TX_(tx->channel_number));
	lan743x_csr_write(adapter, DMAC_INT_EN_SET,
			  DMAC_INT_BIT_TX_IOC_(tx->channel_number));

	/*  start dmac channel */
	lan743x_csr_write(adapter, DMAC_CMD,
			  DMAC_CMD_START_T_(tx->channel_number));
	return 0;
}