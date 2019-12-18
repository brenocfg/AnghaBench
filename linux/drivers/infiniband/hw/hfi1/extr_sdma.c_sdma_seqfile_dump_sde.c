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
typedef  int u8 ;
typedef  int u64 ;
typedef  size_t u16 ;
struct seq_file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  current_state; } ;
struct sdma_engine {size_t descq_head; size_t sdma_mask; struct hw_sdma_desc* descq; int /*<<< orphan*/  descq_full_count; int /*<<< orphan*/  flushlist; int /*<<< orphan*/  descq_tail; int /*<<< orphan*/  tx_head; int /*<<< orphan*/  tx_tail; scalar_t__ ahg_bits; scalar_t__ last_status; int /*<<< orphan*/ * head_dma; TYPE_1__ state; int /*<<< orphan*/  cpu; int /*<<< orphan*/  this_idx; } ;
struct hw_sdma_desc {int /*<<< orphan*/ * qw; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  ENG_ERR_STATUS ; 
 int /*<<< orphan*/  HEAD ; 
 int /*<<< orphan*/  LEN_GEN ; 
 int /*<<< orphan*/  MEMORY ; 
 size_t READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELOAD_CNT ; 
 int /*<<< orphan*/  SD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDE_FMT ; 
 int SDMA_DESC0_BYTE_COUNT_MASK ; 
 int SDMA_DESC0_BYTE_COUNT_SHIFT ; 
 int SDMA_DESC0_FIRST_DESC_FLAG ; 
 int SDMA_DESC0_LAST_DESC_FLAG ; 
 int SDMA_DESC0_PHY_ADDR_MASK ; 
 int SDMA_DESC0_PHY_ADDR_SHIFT ; 
 int SDMA_DESC1_GENERATION_MASK ; 
 int SDMA_DESC1_GENERATION_SHIFT ; 
 int SDMA_DESC1_HEADER_INDEX_SHIFT ; 
 int SDMA_DESC1_HEADER_INDEX_SMASK ; 
 int SDMA_DESC1_HEADER_MODE_SHIFT ; 
 int SDMA_DESC1_HEADER_MODE_SMASK ; 
 int SDMA_DESC1_HEAD_TO_HOST_FLAG ; 
 int SDMA_DESC1_INT_REQ_FLAG ; 
 int /*<<< orphan*/  SEND_DMA_CHECK_SLID ; 
 int /*<<< orphan*/  STATUS ; 
 int /*<<< orphan*/  TAIL ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ read_sde_csr (struct sdma_engine*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdma_state_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 

void sdma_seqfile_dump_sde(struct seq_file *s, struct sdma_engine *sde)
{
	u16 head, tail;
	struct hw_sdma_desc *descqp;
	u64 desc[2];
	u64 addr;
	u8 gen;
	u16 len;

	head = sde->descq_head & sde->sdma_mask;
	tail = READ_ONCE(sde->descq_tail) & sde->sdma_mask;
	seq_printf(s, SDE_FMT, sde->this_idx,
		   sde->cpu,
		   sdma_state_name(sde->state.current_state),
		   (unsigned long long)read_sde_csr(sde, SD(CTRL)),
		   (unsigned long long)read_sde_csr(sde, SD(STATUS)),
		   (unsigned long long)read_sde_csr(sde, SD(ENG_ERR_STATUS)),
		   (unsigned long long)read_sde_csr(sde, SD(TAIL)), tail,
		   (unsigned long long)read_sde_csr(sde, SD(HEAD)), head,
		   (unsigned long long)le64_to_cpu(*sde->head_dma),
		   (unsigned long long)read_sde_csr(sde, SD(MEMORY)),
		   (unsigned long long)read_sde_csr(sde, SD(LEN_GEN)),
		   (unsigned long long)read_sde_csr(sde, SD(RELOAD_CNT)),
		   (unsigned long long)sde->last_status,
		   (unsigned long long)sde->ahg_bits,
		   sde->tx_tail,
		   sde->tx_head,
		   sde->descq_tail,
		   sde->descq_head,
		   !list_empty(&sde->flushlist),
		   sde->descq_full_count,
		   (unsigned long long)read_sde_csr(sde, SEND_DMA_CHECK_SLID));

	/* print info for each entry in the descriptor queue */
	while (head != tail) {
		char flags[6] = { 'x', 'x', 'x', 'x', 0 };

		descqp = &sde->descq[head];
		desc[0] = le64_to_cpu(descqp->qw[0]);
		desc[1] = le64_to_cpu(descqp->qw[1]);
		flags[0] = (desc[1] & SDMA_DESC1_INT_REQ_FLAG) ? 'I' : '-';
		flags[1] = (desc[1] & SDMA_DESC1_HEAD_TO_HOST_FLAG) ?
				'H' : '-';
		flags[2] = (desc[0] & SDMA_DESC0_FIRST_DESC_FLAG) ? 'F' : '-';
		flags[3] = (desc[0] & SDMA_DESC0_LAST_DESC_FLAG) ? 'L' : '-';
		addr = (desc[0] >> SDMA_DESC0_PHY_ADDR_SHIFT)
			& SDMA_DESC0_PHY_ADDR_MASK;
		gen = (desc[1] >> SDMA_DESC1_GENERATION_SHIFT)
			& SDMA_DESC1_GENERATION_MASK;
		len = (desc[0] >> SDMA_DESC0_BYTE_COUNT_SHIFT)
			& SDMA_DESC0_BYTE_COUNT_MASK;
		seq_printf(s,
			   "\tdesc[%u]: flags:%s addr:0x%016llx gen:%u len:%u bytes\n",
			   head, flags, addr, gen, len);
		if (desc[0] & SDMA_DESC0_FIRST_DESC_FLAG)
			seq_printf(s, "\t\tahgidx: %u ahgmode: %u\n",
				   (u8)((desc[1] &
					 SDMA_DESC1_HEADER_INDEX_SMASK) >>
					SDMA_DESC1_HEADER_INDEX_SHIFT),
				   (u8)((desc[1] &
					 SDMA_DESC1_HEADER_MODE_SMASK) >>
					SDMA_DESC1_HEADER_MODE_SHIFT));
		head = (head + 1) & sde->sdma_mask;
	}
}