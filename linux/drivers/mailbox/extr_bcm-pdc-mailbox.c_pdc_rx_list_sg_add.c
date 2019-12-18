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
typedef  scalar_t__ u32 ;
struct scatterlist {int dummy; } ;
struct pdc_state {scalar_t__ nrxpost; int rxout; int nrxd; size_t rx_msg_start; TYPE_1__* rx_ctx; int /*<<< orphan*/  rxnobuf; int /*<<< orphan*/  rxin; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  rxin_numd; } ;

/* Variables and functions */
 scalar_t__ D64_CTRL1_EOT ; 
 int ENOSPC ; 
 scalar_t__ NRXDACTIVE (int /*<<< orphan*/ ,int,scalar_t__) ; 
 scalar_t__ PDC_DMA_BUF_MAX ; 
 int PDC_SUCCESS ; 
 int /*<<< orphan*/  pdc_build_rxd (struct pdc_state*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sg_dma_address (struct scatterlist*) ; 
 scalar_t__ sg_dma_len (struct scatterlist*) ; 
 scalar_t__ sg_nents (struct scatterlist*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int pdc_rx_list_sg_add(struct pdc_state *pdcs, struct scatterlist *sg)
{
	u32 flags = 0;
	u32 rx_avail;

	/*
	 * Num descriptors needed. Conservatively assume we need a descriptor
	 * for every entry from our starting point in the scatterlist.
	 */
	u32 num_desc;
	u32 desc_w = 0;	/* Number of tx descriptors written */
	u32 bufcnt;	/* Number of bytes of buffer pointed to by descriptor */
	dma_addr_t databufptr;	/* DMA address to put in descriptor */

	num_desc = (u32)sg_nents(sg);

	rx_avail = pdcs->nrxpost - NRXDACTIVE(pdcs->rxin, pdcs->rxout,
					      pdcs->nrxpost);
	if (unlikely(num_desc > rx_avail)) {
		pdcs->rxnobuf++;
		return -ENOSPC;
	}

	while (sg) {
		if (unlikely(pdcs->rxout == (pdcs->nrxd - 1)))
			flags = D64_CTRL1_EOT;
		else
			flags = 0;

		/*
		 * If sg buffer larger than PDC limit, split across
		 * multiple descriptors
		 */
		bufcnt = sg_dma_len(sg);
		databufptr = sg_dma_address(sg);
		while (bufcnt > PDC_DMA_BUF_MAX) {
			pdc_build_rxd(pdcs, databufptr, PDC_DMA_BUF_MAX, flags);
			desc_w++;
			bufcnt -= PDC_DMA_BUF_MAX;
			databufptr += PDC_DMA_BUF_MAX;
			if (unlikely(pdcs->rxout == (pdcs->nrxd - 1)))
				flags = D64_CTRL1_EOT;
			else
				flags = 0;
		}
		pdc_build_rxd(pdcs, databufptr, bufcnt, flags);
		desc_w++;
		sg = sg_next(sg);
	}
	pdcs->rx_ctx[pdcs->rx_msg_start].rxin_numd += desc_w;

	return PDC_SUCCESS;
}