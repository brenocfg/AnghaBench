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
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u32 ;
struct xgene_dma_ring {int slots; int size; scalar_t__ owner; TYPE_1__* pdma; int /*<<< orphan*/  buf_num; struct xgene_dma_desc_hw* desc_hw; int /*<<< orphan*/  num; int /*<<< orphan*/  id; int /*<<< orphan*/  cfgsize; int /*<<< orphan*/  desc_paddr; void* state; } ;
struct xgene_dma_desc_hw {int /*<<< orphan*/  m0; } ;
struct TYPE_2__ {scalar_t__ csr_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  XGENE_DMA_DESC_EMPTY_SIGNATURE ; 
 int /*<<< orphan*/  XGENE_DMA_RING_ACCEPTLERR_SET (void*) ; 
 int /*<<< orphan*/  XGENE_DMA_RING_ADDRH_SET (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGENE_DMA_RING_ADDRL_SET (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGENE_DMA_RING_COHERENT_SET (void*) ; 
 scalar_t__ XGENE_DMA_RING_ID ; 
 scalar_t__ XGENE_DMA_RING_ID_BUF ; 
 size_t XGENE_DMA_RING_ID_BUF_SETUP (int /*<<< orphan*/ ) ; 
 size_t XGENE_DMA_RING_ID_SETUP (int /*<<< orphan*/ ) ; 
 scalar_t__ XGENE_DMA_RING_NE_INT_MODE ; 
 int /*<<< orphan*/  XGENE_DMA_RING_NE_INT_MODE_SET (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ XGENE_DMA_RING_OWNER_CPU ; 
 scalar_t__ XGENE_DMA_RING_OWNER_DMA ; 
 int /*<<< orphan*/  XGENE_DMA_RING_RECOMBBUF_SET (void*) ; 
 int /*<<< orphan*/  XGENE_DMA_RING_RECOMTIMEOUTH_SET (void*) ; 
 int /*<<< orphan*/  XGENE_DMA_RING_RECOMTIMEOUTL_SET (void*) ; 
 int /*<<< orphan*/  XGENE_DMA_RING_SELTHRSH_SET (void*) ; 
 int /*<<< orphan*/  XGENE_DMA_RING_SIZE_SET (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGENE_DMA_RING_TYPE_REGULAR ; 
 int /*<<< orphan*/  XGENE_DMA_RING_TYPE_SET (void*,int /*<<< orphan*/ ) ; 
 int XGENE_DMA_RING_WQ_DESC_SIZE ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 size_t ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (size_t,scalar_t__) ; 
 int /*<<< orphan*/  xgene_dma_clr_ring_state (struct xgene_dma_ring*) ; 
 int /*<<< orphan*/  xgene_dma_wr_ring_state (struct xgene_dma_ring*) ; 

__attribute__((used)) static void xgene_dma_setup_ring(struct xgene_dma_ring *ring)
{
	void *ring_cfg = ring->state;
	u64 addr = ring->desc_paddr;
	u32 i, val;

	ring->slots = ring->size / XGENE_DMA_RING_WQ_DESC_SIZE;

	/* Clear DMA ring state */
	xgene_dma_clr_ring_state(ring);

	/* Set DMA ring type */
	XGENE_DMA_RING_TYPE_SET(ring_cfg, XGENE_DMA_RING_TYPE_REGULAR);

	if (ring->owner == XGENE_DMA_RING_OWNER_DMA) {
		/* Set recombination buffer and timeout */
		XGENE_DMA_RING_RECOMBBUF_SET(ring_cfg);
		XGENE_DMA_RING_RECOMTIMEOUTL_SET(ring_cfg);
		XGENE_DMA_RING_RECOMTIMEOUTH_SET(ring_cfg);
	}

	/* Initialize DMA ring state */
	XGENE_DMA_RING_SELTHRSH_SET(ring_cfg);
	XGENE_DMA_RING_ACCEPTLERR_SET(ring_cfg);
	XGENE_DMA_RING_COHERENT_SET(ring_cfg);
	XGENE_DMA_RING_ADDRL_SET(ring_cfg, addr);
	XGENE_DMA_RING_ADDRH_SET(ring_cfg, addr);
	XGENE_DMA_RING_SIZE_SET(ring_cfg, ring->cfgsize);

	/* Write DMA ring configurations */
	xgene_dma_wr_ring_state(ring);

	/* Set DMA ring id */
	iowrite32(XGENE_DMA_RING_ID_SETUP(ring->id),
		  ring->pdma->csr_ring + XGENE_DMA_RING_ID);

	/* Set DMA ring buffer */
	iowrite32(XGENE_DMA_RING_ID_BUF_SETUP(ring->num),
		  ring->pdma->csr_ring + XGENE_DMA_RING_ID_BUF);

	if (ring->owner != XGENE_DMA_RING_OWNER_CPU)
		return;

	/* Set empty signature to DMA Rx ring descriptors */
	for (i = 0; i < ring->slots; i++) {
		struct xgene_dma_desc_hw *desc;

		desc = &ring->desc_hw[i];
		desc->m0 = cpu_to_le64(XGENE_DMA_DESC_EMPTY_SIGNATURE);
	}

	/* Enable DMA Rx ring interrupt */
	val = ioread32(ring->pdma->csr_ring + XGENE_DMA_RING_NE_INT_MODE);
	XGENE_DMA_RING_NE_INT_MODE_SET(val, ring->buf_num);
	iowrite32(val, ring->pdma->csr_ring + XGENE_DMA_RING_NE_INT_MODE);
}