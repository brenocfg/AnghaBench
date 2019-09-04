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
struct xor_cb {int cbc; } ;
struct ppc440spe_adma_desc_slot {int src_cnt; int dst_cnt; int /*<<< orphan*/ * hw_next; struct xor_cb* hw_desc; } ;

/* Variables and functions */
 unsigned long DMA_PREP_INTERRUPT ; 
 int XOR_CBCR_CBCE_BIT ; 
 int XOR_CBCR_TGT_BIT ; 
 int /*<<< orphan*/  memset (struct xor_cb*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ppc440spe_desc_init_xor(struct ppc440spe_adma_desc_slot *desc,
					 int src_cnt, unsigned long flags)
{
	struct xor_cb *hw_desc = desc->hw_desc;

	memset(desc->hw_desc, 0, sizeof(struct xor_cb));
	desc->hw_next = NULL;
	desc->src_cnt = src_cnt;
	desc->dst_cnt = 1;

	hw_desc->cbc = XOR_CBCR_TGT_BIT | src_cnt;
	if (flags & DMA_PREP_INTERRUPT)
		/* Enable interrupt on completion */
		hw_desc->cbc |= XOR_CBCR_CBCE_BIT;
}