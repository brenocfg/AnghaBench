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
struct ppc440spe_adma_desc_slot {int dummy; } ;
struct ppc440spe_adma_chan {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CDB_SG_DST1 ; 
 int /*<<< orphan*/  DMA_CUED_MULT1_OFF ; 
 int /*<<< orphan*/  DMA_CUED_XOR_BASE ; 
 int /*<<< orphan*/  DMA_CUED_XOR_HB ; 
 int /*<<< orphan*/  ppc440spe_desc_set_dest_addr (struct ppc440spe_adma_desc_slot*,struct ppc440spe_adma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppc440spe_desc_set_src_addr (struct ppc440spe_adma_desc_slot*,struct ppc440spe_adma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppc440spe_desc_set_src_mult (struct ppc440spe_adma_desc_slot*,struct ppc440spe_adma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ppc440spe_adma_pq_zero_op(struct ppc440spe_adma_desc_slot *iter,
		struct ppc440spe_adma_chan *chan, dma_addr_t addr)
{
	/*  To clear destinations update the descriptor
	 * (P or Q depending on index) as follows:
	 * addr is destination (0 corresponds to SG2):
	 */
	ppc440spe_desc_set_dest_addr(iter, chan, DMA_CUED_XOR_BASE, addr, 0);

	/* ... and the addr is source: */
	ppc440spe_desc_set_src_addr(iter, chan, 0, DMA_CUED_XOR_HB, addr);

	/* addr is always SG2 then the mult is always DST1 */
	ppc440spe_desc_set_src_mult(iter, chan, DMA_CUED_MULT1_OFF,
				    DMA_CDB_SG_DST1, 1);
}