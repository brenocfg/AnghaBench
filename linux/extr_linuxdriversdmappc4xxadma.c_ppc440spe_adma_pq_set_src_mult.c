#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  chan; } ;
struct ppc440spe_adma_desc_slot {int dst_cnt; int descs_per_op; struct ppc440spe_adma_desc_slot* group_head; int /*<<< orphan*/  flags; TYPE_1__ async_tx; } ;
struct ppc440spe_adma_chan {TYPE_2__* device; } ;
struct TYPE_4__ {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CDB_SG_DST1 ; 
 int /*<<< orphan*/  DMA_CDB_SG_DST2 ; 
 int /*<<< orphan*/  DMA_CDB_SG_SRC ; 
 int /*<<< orphan*/  DMA_CUED_MULT1_OFF ; 
 int /*<<< orphan*/  PPC440SPE_DESC_RXOR ; 
 int /*<<< orphan*/  PPC440SPE_DESC_RXOR12 ; 
#define  PPC440SPE_DMA0_ID 130 
#define  PPC440SPE_DMA1_ID 129 
#define  PPC440SPE_XOR_ID 128 
 int /*<<< orphan*/  PPC440SPE_ZERO_P ; 
 int /*<<< orphan*/  PPC440SPE_ZERO_Q ; 
 int /*<<< orphan*/  likely (struct ppc440spe_adma_desc_slot*) ; 
 int /*<<< orphan*/  ppc440spe_adma_dma2rxor_set_mult (struct ppc440spe_adma_desc_slot*,int,unsigned char) ; 
 int /*<<< orphan*/  ppc440spe_desc_set_src_mult (struct ppc440spe_adma_desc_slot*,struct ppc440spe_adma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ppc440spe_adma_desc_slot* ppc440spe_get_group_entry (struct ppc440spe_adma_desc_slot*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ppc440spe_adma_chan* to_ppc440spe_adma_chan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlikely (struct ppc440spe_adma_desc_slot*) ; 

__attribute__((used)) static void ppc440spe_adma_pq_set_src_mult(
		struct ppc440spe_adma_desc_slot *sw_desc,
		unsigned char mult, int index, int dst_pos)
{
	struct ppc440spe_adma_chan *chan;
	u32 mult_idx, mult_dst;
	struct ppc440spe_adma_desc_slot *iter = NULL, *iter1 = NULL;

	chan = to_ppc440spe_adma_chan(sw_desc->async_tx.chan);

	switch (chan->device->id) {
	case PPC440SPE_DMA0_ID:
	case PPC440SPE_DMA1_ID:
		if (test_bit(PPC440SPE_DESC_RXOR, &sw_desc->flags)) {
			int region = test_bit(PPC440SPE_DESC_RXOR12,
					&sw_desc->flags) ? 2 : 3;

			if (index < region) {
				/* RXOR multipliers */
				iter = ppc440spe_get_group_entry(sw_desc,
					sw_desc->dst_cnt - 1);
				if (sw_desc->dst_cnt == 2)
					iter1 = ppc440spe_get_group_entry(
							sw_desc, 0);

				mult_idx = DMA_CUED_MULT1_OFF + (index << 3);
				mult_dst = DMA_CDB_SG_SRC;
			} else {
				/* WXOR multiplier */
				iter = ppc440spe_get_group_entry(sw_desc,
							index - region +
							sw_desc->dst_cnt);
				mult_idx = DMA_CUED_MULT1_OFF;
				mult_dst = dst_pos ? DMA_CDB_SG_DST2 :
						     DMA_CDB_SG_DST1;
			}
		} else {
			int znum = 0;

			/* WXOR-only;
			 * skip first slots with destinations (if ZERO_DST has
			 * place)
			 */
			if (test_bit(PPC440SPE_ZERO_P, &sw_desc->flags))
				znum++;
			if (test_bit(PPC440SPE_ZERO_Q, &sw_desc->flags))
				znum++;

			iter = ppc440spe_get_group_entry(sw_desc, index + znum);
			mult_idx = DMA_CUED_MULT1_OFF;
			mult_dst = dst_pos ? DMA_CDB_SG_DST2 : DMA_CDB_SG_DST1;
		}

		if (likely(iter)) {
			ppc440spe_desc_set_src_mult(iter, chan,
				mult_idx, mult_dst, mult);

			if (unlikely(iter1)) {
				/* if we have two destinations for RXOR, then
				 * we've just set Q mult. Set-up P now.
				 */
				ppc440spe_desc_set_src_mult(iter1, chan,
					mult_idx, mult_dst, 1);
			}

		}
		break;

	case PPC440SPE_XOR_ID:
		iter = sw_desc->group_head;
		if (sw_desc->dst_cnt == 2) {
			/* both P & Q calculations required; set P mult here */
			ppc440spe_adma_dma2rxor_set_mult(iter, index, 1);

			/* and then set Q mult */
			iter = ppc440spe_get_group_entry(sw_desc,
			       sw_desc->descs_per_op);
		}
		ppc440spe_adma_dma2rxor_set_mult(iter, index, mult);
		break;
	}
}