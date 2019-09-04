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
struct TYPE_4__ {scalar_t__ dma; } ;
struct alx_hw {int dummy; } ;
struct alx_priv {int num_napi; int tx_ringsz; int rx_ringsz; int rxbuf_size; struct alx_napi** qnapi; TYPE_1__ descmem; struct alx_hw hw; } ;
struct alx_napi {TYPE_3__* rxq; TYPE_2__* txq; } ;
struct TYPE_6__ {int rrd_dma; int rfd_dma; scalar_t__ rrd_read_idx; scalar_t__ write_idx; scalar_t__ read_idx; } ;
struct TYPE_5__ {size_t queue_idx; int tpd_dma; scalar_t__ write_idx; scalar_t__ read_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALX_RFD_ADDR_LO ; 
 int /*<<< orphan*/  ALX_RFD_BUF_SZ ; 
 int /*<<< orphan*/  ALX_RFD_RING_SZ ; 
 int /*<<< orphan*/  ALX_RRD_ADDR_LO ; 
 int /*<<< orphan*/  ALX_RRD_RING_SZ ; 
 int /*<<< orphan*/  ALX_RX_BASE_ADDR_HI ; 
 int /*<<< orphan*/  ALX_SRAM9 ; 
 int ALX_SRAM_LOAD_PTR ; 
 int /*<<< orphan*/  ALX_TPD_RING_SZ ; 
 int /*<<< orphan*/  ALX_TX_BASE_ADDR_HI ; 
 int /*<<< orphan*/  alx_write_mem32 (struct alx_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * txring_header_reg ; 

__attribute__((used)) static void alx_init_ring_ptrs(struct alx_priv *alx)
{
	struct alx_hw *hw = &alx->hw;
	u32 addr_hi = ((u64)alx->descmem.dma) >> 32;
	struct alx_napi *np;
	int i;

	for (i = 0; i < alx->num_napi; i++) {
		np = alx->qnapi[i];
		if (np->txq) {
			np->txq->read_idx = 0;
			np->txq->write_idx = 0;
			alx_write_mem32(hw,
					txring_header_reg[np->txq->queue_idx],
					np->txq->tpd_dma);
		}

		if (np->rxq) {
			np->rxq->read_idx = 0;
			np->rxq->write_idx = 0;
			np->rxq->rrd_read_idx = 0;
			alx_write_mem32(hw, ALX_RRD_ADDR_LO, np->rxq->rrd_dma);
			alx_write_mem32(hw, ALX_RFD_ADDR_LO, np->rxq->rfd_dma);
		}
	}

	alx_write_mem32(hw, ALX_TX_BASE_ADDR_HI, addr_hi);
	alx_write_mem32(hw, ALX_TPD_RING_SZ, alx->tx_ringsz);

	alx_write_mem32(hw, ALX_RX_BASE_ADDR_HI, addr_hi);
	alx_write_mem32(hw, ALX_RRD_RING_SZ, alx->rx_ringsz);
	alx_write_mem32(hw, ALX_RFD_RING_SZ, alx->rx_ringsz);
	alx_write_mem32(hw, ALX_RFD_BUF_SZ, alx->rxbuf_size);

	/* load these pointers into the chip */
	alx_write_mem32(hw, ALX_SRAM9, ALX_SRAM_LOAD_PTR);
}