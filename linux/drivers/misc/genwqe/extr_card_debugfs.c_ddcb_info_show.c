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
struct seq_file {struct genwqe_dev* private; } ;
struct ddcb_queue {long long ddcb_max; struct ddcb* ddcb_vaddr; int /*<<< orphan*/  ddcb_next; int /*<<< orphan*/  ddcb_act; int /*<<< orphan*/  IO_QUEUE_LRW; int /*<<< orphan*/  IO_QUEUE_ERRCNTS; int /*<<< orphan*/  IO_QUEUE_WTIME; int /*<<< orphan*/  IO_QUEUE_OFFSET; int /*<<< orphan*/  IO_QUEUE_WRAP; int /*<<< orphan*/  IO_QUEUE_INITSQN; int /*<<< orphan*/  IO_QUEUE_SEGMENT; int /*<<< orphan*/  IO_QUEUE_STATUS; int /*<<< orphan*/  IO_QUEUE_CONFIG; int /*<<< orphan*/  wait_on_busy; int /*<<< orphan*/  return_on_busy; int /*<<< orphan*/  ddcbs_completed; int /*<<< orphan*/  ddcbs_max_in_flight; int /*<<< orphan*/  ddcbs_in_flight; scalar_t__ ddcb_daddr; } ;
struct genwqe_dev {int /*<<< orphan*/  irqs_processed; struct ddcb_queue queue; } ;
struct ddcb {int /*<<< orphan*/  cmd; int /*<<< orphan*/  priv_64; int /*<<< orphan*/  shi; int /*<<< orphan*/  hsi; int /*<<< orphan*/  seqnum_16; int /*<<< orphan*/  retc_16; } ;

/* Variables and functions */
 long long DDCB_LENGTH ; 
 int /*<<< orphan*/  __genwqe_readq (struct genwqe_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,long long,long long,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int ddcb_info_show(struct seq_file *s, void *unused)
{
	struct genwqe_dev *cd = s->private;
	unsigned int i;
	struct ddcb_queue *queue;
	struct ddcb *pddcb;

	queue = &cd->queue;
	seq_puts(s, "DDCB QUEUE:\n");
	seq_printf(s, "  ddcb_max:            %d\n"
		   "  ddcb_daddr:          %016llx - %016llx\n"
		   "  ddcb_vaddr:          %p\n"
		   "  ddcbs_in_flight:     %u\n"
		   "  ddcbs_max_in_flight: %u\n"
		   "  ddcbs_completed:     %u\n"
		   "  return_on_busy:      %u\n"
		   "  wait_on_busy:        %u\n"
		   "  irqs_processed:      %u\n",
		   queue->ddcb_max, (long long)queue->ddcb_daddr,
		   (long long)queue->ddcb_daddr +
		   (queue->ddcb_max * DDCB_LENGTH),
		   queue->ddcb_vaddr, queue->ddcbs_in_flight,
		   queue->ddcbs_max_in_flight, queue->ddcbs_completed,
		   queue->return_on_busy, queue->wait_on_busy,
		   cd->irqs_processed);

	/* Hardware State */
	seq_printf(s, "  0x%08x 0x%016llx IO_QUEUE_CONFIG\n"
		   "  0x%08x 0x%016llx IO_QUEUE_STATUS\n"
		   "  0x%08x 0x%016llx IO_QUEUE_SEGMENT\n"
		   "  0x%08x 0x%016llx IO_QUEUE_INITSQN\n"
		   "  0x%08x 0x%016llx IO_QUEUE_WRAP\n"
		   "  0x%08x 0x%016llx IO_QUEUE_OFFSET\n"
		   "  0x%08x 0x%016llx IO_QUEUE_WTIME\n"
		   "  0x%08x 0x%016llx IO_QUEUE_ERRCNTS\n"
		   "  0x%08x 0x%016llx IO_QUEUE_LRW\n",
		   queue->IO_QUEUE_CONFIG,
		   __genwqe_readq(cd, queue->IO_QUEUE_CONFIG),
		   queue->IO_QUEUE_STATUS,
		   __genwqe_readq(cd, queue->IO_QUEUE_STATUS),
		   queue->IO_QUEUE_SEGMENT,
		   __genwqe_readq(cd, queue->IO_QUEUE_SEGMENT),
		   queue->IO_QUEUE_INITSQN,
		   __genwqe_readq(cd, queue->IO_QUEUE_INITSQN),
		   queue->IO_QUEUE_WRAP,
		   __genwqe_readq(cd, queue->IO_QUEUE_WRAP),
		   queue->IO_QUEUE_OFFSET,
		   __genwqe_readq(cd, queue->IO_QUEUE_OFFSET),
		   queue->IO_QUEUE_WTIME,
		   __genwqe_readq(cd, queue->IO_QUEUE_WTIME),
		   queue->IO_QUEUE_ERRCNTS,
		   __genwqe_readq(cd, queue->IO_QUEUE_ERRCNTS),
		   queue->IO_QUEUE_LRW,
		   __genwqe_readq(cd, queue->IO_QUEUE_LRW));

	seq_printf(s, "DDCB list (ddcb_act=%d/ddcb_next=%d):\n",
		   queue->ddcb_act, queue->ddcb_next);

	pddcb = queue->ddcb_vaddr;
	for (i = 0; i < queue->ddcb_max; i++) {
		seq_printf(s, "  %-3d: RETC=%03x SEQ=%04x HSI/SHI=%02x/%02x ",
			   i, be16_to_cpu(pddcb->retc_16),
			   be16_to_cpu(pddcb->seqnum_16),
			   pddcb->hsi, pddcb->shi);
		seq_printf(s, "PRIV=%06llx CMD=%02x\n",
			   be64_to_cpu(pddcb->priv_64), pddcb->cmd);
		pddcb++;
	}
	return 0;
}