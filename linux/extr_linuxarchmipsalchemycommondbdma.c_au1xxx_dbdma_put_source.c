#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  unsigned long dma_addr_t ;
struct TYPE_6__ {TYPE_3__* put_ptr; TYPE_1__* chan_ptr; } ;
typedef  TYPE_2__ chan_tab_t ;
struct TYPE_7__ {int dscr_cmd0; unsigned long dscr_source0; int dscr_cmd1; int /*<<< orphan*/  dscr_nxtptr; } ;
typedef  TYPE_3__ au1x_ddma_desc_t ;
struct TYPE_5__ {scalar_t__ ddma_dbell; } ;

/* Variables and functions */
 int DDMA_FLAGS_IE ; 
 int DDMA_FLAGS_NOIE ; 
 int DSCR_CMD0_IE ; 
 int DSCR_CMD0_V ; 
 int /*<<< orphan*/  DSCR_GET_NXTPTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cache_wback_inv (unsigned long,int) ; 
 TYPE_3__* phys_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

u32 au1xxx_dbdma_put_source(u32 chanid, dma_addr_t buf, int nbytes, u32 flags)
{
	chan_tab_t		*ctp;
	au1x_ddma_desc_t	*dp;

	/*
	 * I guess we could check this to be within the
	 * range of the table......
	 */
	ctp = *(chan_tab_t **)chanid;

	/*
	 * We should have multiple callers for a particular channel,
	 * an interrupt doesn't affect this pointer nor the descriptor,
	 * so no locking should be needed.
	 */
	dp = ctp->put_ptr;

	/*
	 * If the descriptor is valid, we are way ahead of the DMA
	 * engine, so just return an error condition.
	 */
	if (dp->dscr_cmd0 & DSCR_CMD0_V)
		return 0;

	/* Load up buffer address and byte count. */
	dp->dscr_source0 = buf & ~0UL;
	dp->dscr_cmd1 = nbytes;
	/* Check flags */
	if (flags & DDMA_FLAGS_IE)
		dp->dscr_cmd0 |= DSCR_CMD0_IE;
	if (flags & DDMA_FLAGS_NOIE)
		dp->dscr_cmd0 &= ~DSCR_CMD0_IE;

	/*
	 * There is an errata on the Au1200/Au1550 parts that could result
	 * in "stale" data being DMA'ed. It has to do with the snoop logic on
	 * the cache eviction buffer.  DMA_NONCOHERENT is on by default for
	 * these parts. If it is fixed in the future, these dma_cache_inv will
	 * just be nothing more than empty macros. See io.h.
	 */
	dma_cache_wback_inv((unsigned long)buf, nbytes);
	dp->dscr_cmd0 |= DSCR_CMD0_V;	/* Let it rip */
	wmb(); /* drain writebuffer */
	dma_cache_wback_inv((unsigned long)dp, sizeof(*dp));
	ctp->chan_ptr->ddma_dbell = 0;

	/* Get next descriptor pointer. */
	ctp->put_ptr = phys_to_virt(DSCR_GET_NXTPTR(dp->dscr_nxtptr));

	/* Return something non-zero. */
	return nbytes;
}