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
typedef  scalar_t__ u32 ;
struct scatterlist {int dummy; } ;
struct pdc_state {scalar_t__ ntxpost; size_t txout; size_t tx_msg_start; scalar_t__* txin_numd; int ntxd; struct scatterlist** src_sg; int /*<<< orphan*/  txnobuf; int /*<<< orphan*/  txin; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 scalar_t__ D64_CTRL1_EOF ; 
 scalar_t__ D64_CTRL1_EOT ; 
 scalar_t__ D64_CTRL1_IOC ; 
 scalar_t__ D64_CTRL1_SOF ; 
 int ENOSPC ; 
 scalar_t__ NTXDACTIVE (int /*<<< orphan*/ ,size_t,scalar_t__) ; 
 scalar_t__ PDC_DMA_BUF_MAX ; 
 int PDC_SUCCESS ; 
 int /*<<< orphan*/  pdc_build_txd (struct pdc_state*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sg_dma_address (struct scatterlist*) ; 
 scalar_t__ sg_dma_len (struct scatterlist*) ; 
 scalar_t__ sg_nents (struct scatterlist*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int pdc_tx_list_sg_add(struct pdc_state *pdcs, struct scatterlist *sg)
{
	u32 flags = 0;
	u32 eot;
	u32 tx_avail;

	/*
	 * Num descriptors needed. Conservatively assume we need a descriptor
	 * for every entry in sg.
	 */
	u32 num_desc;
	u32 desc_w = 0;	/* Number of tx descriptors written */
	u32 bufcnt;	/* Number of bytes of buffer pointed to by descriptor */
	dma_addr_t databufptr;	/* DMA address to put in descriptor */

	num_desc = (u32)sg_nents(sg);

	/* check whether enough tx descriptors are available */
	tx_avail = pdcs->ntxpost - NTXDACTIVE(pdcs->txin, pdcs->txout,
					      pdcs->ntxpost);
	if (unlikely(num_desc > tx_avail)) {
		pdcs->txnobuf++;
		return -ENOSPC;
	}

	/* build tx descriptors */
	if (pdcs->tx_msg_start == pdcs->txout) {
		/* Start of frame */
		pdcs->txin_numd[pdcs->tx_msg_start] = 0;
		pdcs->src_sg[pdcs->txout] = sg;
		flags = D64_CTRL1_SOF;
	}

	while (sg) {
		if (unlikely(pdcs->txout == (pdcs->ntxd - 1)))
			eot = D64_CTRL1_EOT;
		else
			eot = 0;

		/*
		 * If sg buffer larger than PDC limit, split across
		 * multiple descriptors
		 */
		bufcnt = sg_dma_len(sg);
		databufptr = sg_dma_address(sg);
		while (bufcnt > PDC_DMA_BUF_MAX) {
			pdc_build_txd(pdcs, databufptr, PDC_DMA_BUF_MAX,
				      flags | eot);
			desc_w++;
			bufcnt -= PDC_DMA_BUF_MAX;
			databufptr += PDC_DMA_BUF_MAX;
			if (unlikely(pdcs->txout == (pdcs->ntxd - 1)))
				eot = D64_CTRL1_EOT;
			else
				eot = 0;
		}
		sg = sg_next(sg);
		if (!sg)
			/* Writing last descriptor for frame */
			flags |= (D64_CTRL1_EOF | D64_CTRL1_IOC);
		pdc_build_txd(pdcs, databufptr, bufcnt, flags | eot);
		desc_w++;
		/* Clear start of frame after first descriptor */
		flags &= ~D64_CTRL1_SOF;
	}
	pdcs->txin_numd[pdcs->tx_msg_start] += desc_w;

	return PDC_SUCCESS;
}