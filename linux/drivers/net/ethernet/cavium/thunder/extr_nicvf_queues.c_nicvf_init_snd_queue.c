#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_6__ {int /*<<< orphan*/  base; } ;
struct snd_queue {int xdp_free_cnt; int is_xdp; int /*<<< orphan*/  tso_hdrs; int /*<<< orphan*/  tso_hdrs_phys; int /*<<< orphan*/  free_cnt; scalar_t__ xdp_desc_cnt; int /*<<< orphan*/ * xdp_page; int /*<<< orphan*/  thresh; scalar_t__ tail; scalar_t__ head; void* skbuff; TYPE_3__ dmem; int /*<<< orphan*/  desc; } ;
struct nicvf {int sqs_id; TYPE_2__* pdev; TYPE_1__* pnicvf; scalar_t__ sqs_mode; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int xdp_tx_queues; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_SND_QUEUES_PER_QS ; 
 int /*<<< orphan*/  NICVF_SQ_BASE_ALIGN_BYTES ; 
 int /*<<< orphan*/  SND_QUEUE_DESC_SIZE ; 
 int /*<<< orphan*/  SND_QUEUE_THRESH ; 
 int TSO_HEADER_SIZE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int nicvf_alloc_q_desc_mem (struct nicvf*,TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nicvf_init_snd_queue(struct nicvf *nic,
				struct snd_queue *sq, int q_len, int qidx)
{
	int err;

	err = nicvf_alloc_q_desc_mem(nic, &sq->dmem, q_len, SND_QUEUE_DESC_SIZE,
				     NICVF_SQ_BASE_ALIGN_BYTES);
	if (err)
		return err;

	sq->desc = sq->dmem.base;
	sq->skbuff = kcalloc(q_len, sizeof(u64), GFP_KERNEL);
	if (!sq->skbuff)
		return -ENOMEM;

	sq->head = 0;
	sq->tail = 0;
	sq->thresh = SND_QUEUE_THRESH;

	/* Check if this SQ is a XDP TX queue */
	if (nic->sqs_mode)
		qidx += ((nic->sqs_id + 1) * MAX_SND_QUEUES_PER_QS);
	if (qidx < nic->pnicvf->xdp_tx_queues) {
		/* Alloc memory to save page pointers for XDP_TX */
		sq->xdp_page = kcalloc(q_len, sizeof(u64), GFP_KERNEL);
		if (!sq->xdp_page)
			return -ENOMEM;
		sq->xdp_desc_cnt = 0;
		sq->xdp_free_cnt = q_len - 1;
		sq->is_xdp = true;
	} else {
		sq->xdp_page = NULL;
		sq->xdp_desc_cnt = 0;
		sq->xdp_free_cnt = 0;
		sq->is_xdp = false;

		atomic_set(&sq->free_cnt, q_len - 1);

		/* Preallocate memory for TSO segment's header */
		sq->tso_hdrs = dma_alloc_coherent(&nic->pdev->dev,
						  q_len * TSO_HEADER_SIZE,
						  &sq->tso_hdrs_phys,
						  GFP_KERNEL);
		if (!sq->tso_hdrs)
			return -ENOMEM;
	}

	return 0;
}