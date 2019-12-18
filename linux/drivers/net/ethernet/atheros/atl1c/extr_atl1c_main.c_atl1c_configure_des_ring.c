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
struct atl1c_tpd_ring {int dma; int count; } ;
struct atl1c_rrd_ring {int dma; int count; } ;
struct atl1c_rfd_ring {int dma; int count; } ;
struct atl1c_hw {scalar_t__ nic_type; } ;
struct atl1c_adapter {int rx_buffer_len; scalar_t__ tpd_ring; struct atl1c_rrd_ring rrd_ring; struct atl1c_rfd_ring rfd_ring; struct atl1c_hw hw; } ;

/* Variables and functions */
 int AT_DMA_HI_ADDR_MASK ; 
 int AT_DMA_LO_ADDR_MASK ; 
 int /*<<< orphan*/  AT_WRITE_REG (struct atl1c_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_LOAD_PTR ; 
 int /*<<< orphan*/  REG_RFD0_HEAD_ADDR_LO ; 
 int /*<<< orphan*/  REG_RFD_RING_SIZE ; 
 int /*<<< orphan*/  REG_RRD0_HEAD_ADDR_LO ; 
 int /*<<< orphan*/  REG_RRD_RING_SIZE ; 
 int /*<<< orphan*/  REG_RXD_DMA_CTRL ; 
 int /*<<< orphan*/  REG_RX_BASE_ADDR_HI ; 
 int /*<<< orphan*/  REG_RX_BUF_SIZE ; 
 int /*<<< orphan*/  REG_SRAM_RFD0_INFO ; 
 int /*<<< orphan*/  REG_SRAM_RXF_ADDR ; 
 int /*<<< orphan*/  REG_SRAM_RXF_LEN ; 
 int /*<<< orphan*/  REG_SRAM_TRD_ADDR ; 
 int /*<<< orphan*/  REG_SRAM_TXF_ADDR ; 
 int /*<<< orphan*/  REG_SRAM_TXF_LEN ; 
 int /*<<< orphan*/  REG_TPD_PRI0_ADDR_LO ; 
 int /*<<< orphan*/  REG_TPD_PRI1_ADDR_LO ; 
 int /*<<< orphan*/  REG_TPD_RING_SIZE ; 
 int /*<<< orphan*/  REG_TXF_WATER_MARK ; 
 int /*<<< orphan*/  REG_TX_BASE_ADDR_HI ; 
 int RFD_RING_SIZE_MASK ; 
 int RRD_RING_SIZE_MASK ; 
 int RX_BUF_SIZE_MASK ; 
 int TPD_RING_SIZE_MASK ; 
 scalar_t__ athr_l2c_b ; 
 size_t atl1c_trans_high ; 
 size_t atl1c_trans_normal ; 

__attribute__((used)) static void atl1c_configure_des_ring(struct atl1c_adapter *adapter)
{
	struct atl1c_hw *hw = &adapter->hw;
	struct atl1c_rfd_ring *rfd_ring = &adapter->rfd_ring;
	struct atl1c_rrd_ring *rrd_ring = &adapter->rrd_ring;
	struct atl1c_tpd_ring *tpd_ring = (struct atl1c_tpd_ring *)
				adapter->tpd_ring;

	/* TPD */
	AT_WRITE_REG(hw, REG_TX_BASE_ADDR_HI,
			(u32)((tpd_ring[atl1c_trans_normal].dma &
				AT_DMA_HI_ADDR_MASK) >> 32));
	/* just enable normal priority TX queue */
	AT_WRITE_REG(hw, REG_TPD_PRI0_ADDR_LO,
			(u32)(tpd_ring[atl1c_trans_normal].dma &
				AT_DMA_LO_ADDR_MASK));
	AT_WRITE_REG(hw, REG_TPD_PRI1_ADDR_LO,
			(u32)(tpd_ring[atl1c_trans_high].dma &
				AT_DMA_LO_ADDR_MASK));
	AT_WRITE_REG(hw, REG_TPD_RING_SIZE,
			(u32)(tpd_ring[0].count & TPD_RING_SIZE_MASK));


	/* RFD */
	AT_WRITE_REG(hw, REG_RX_BASE_ADDR_HI,
			(u32)((rfd_ring->dma & AT_DMA_HI_ADDR_MASK) >> 32));
	AT_WRITE_REG(hw, REG_RFD0_HEAD_ADDR_LO,
			(u32)(rfd_ring->dma & AT_DMA_LO_ADDR_MASK));

	AT_WRITE_REG(hw, REG_RFD_RING_SIZE,
			rfd_ring->count & RFD_RING_SIZE_MASK);
	AT_WRITE_REG(hw, REG_RX_BUF_SIZE,
			adapter->rx_buffer_len & RX_BUF_SIZE_MASK);

	/* RRD */
	AT_WRITE_REG(hw, REG_RRD0_HEAD_ADDR_LO,
			(u32)(rrd_ring->dma & AT_DMA_LO_ADDR_MASK));
	AT_WRITE_REG(hw, REG_RRD_RING_SIZE,
			(rrd_ring->count & RRD_RING_SIZE_MASK));

	if (hw->nic_type == athr_l2c_b) {
		AT_WRITE_REG(hw, REG_SRAM_RXF_LEN, 0x02a0L);
		AT_WRITE_REG(hw, REG_SRAM_TXF_LEN, 0x0100L);
		AT_WRITE_REG(hw, REG_SRAM_RXF_ADDR, 0x029f0000L);
		AT_WRITE_REG(hw, REG_SRAM_RFD0_INFO, 0x02bf02a0L);
		AT_WRITE_REG(hw, REG_SRAM_TXF_ADDR, 0x03bf02c0L);
		AT_WRITE_REG(hw, REG_SRAM_TRD_ADDR, 0x03df03c0L);
		AT_WRITE_REG(hw, REG_TXF_WATER_MARK, 0);	/* TX watermark, to enter l1 state.*/
		AT_WRITE_REG(hw, REG_RXD_DMA_CTRL, 0);		/* RXD threshold.*/
	}
	/* Load all of base address above */
	AT_WRITE_REG(hw, REG_LOAD_PTR, 1);
}