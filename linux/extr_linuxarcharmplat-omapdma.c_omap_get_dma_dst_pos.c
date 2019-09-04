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
typedef  int dma_addr_t ;
struct TYPE_2__ {int (* dma_read ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CDAC ; 
 int /*<<< orphan*/  CDSA ; 
 int /*<<< orphan*/  CPC ; 
 scalar_t__ dma_omap1 () ; 
 scalar_t__ dma_omap15xx () ; 
 TYPE_1__* p ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 
 int stub2 (int /*<<< orphan*/ ,int) ; 
 int stub3 (int /*<<< orphan*/ ,int) ; 
 int stub4 (int /*<<< orphan*/ ,int) ; 
 int stub5 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

dma_addr_t omap_get_dma_dst_pos(int lch)
{
	dma_addr_t offset = 0;

	if (dma_omap15xx())
		offset = p->dma_read(CPC, lch);
	else
		offset = p->dma_read(CDAC, lch);

	/*
	 * omap 3.2/3.3 erratum: sometimes 0 is returned if CSAC/CDAC is
	 * read before the DMA controller finished disabling the channel.
	 */
	if (!dma_omap15xx() && offset == 0) {
		offset = p->dma_read(CDAC, lch);
		/*
		 * CDAC == 0 indicates that the DMA transfer on the channel has
		 * not been started (no data has been transferred so far).
		 * Return the programmed destination start address in this case.
		 */
		if (unlikely(!offset))
			offset = p->dma_read(CDSA, lch);
	}

	if (dma_omap1())
		offset |= (p->dma_read(CDSA, lch) & 0xFFFF0000);

	return offset;
}