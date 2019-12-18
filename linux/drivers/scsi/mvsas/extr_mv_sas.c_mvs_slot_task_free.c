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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  smp_req; int /*<<< orphan*/  smp_resp; } ;
struct sas_task {int task_proto; int /*<<< orphan*/ * lldd_task; TYPE_1__ smp_task; int /*<<< orphan*/  data_dir; int /*<<< orphan*/ * scatter; } ;
struct mvs_slot_info {int n_elem; int slot_tag; int /*<<< orphan*/ * port; int /*<<< orphan*/ * task; int /*<<< orphan*/  entry; int /*<<< orphan*/ * buf; int /*<<< orphan*/  buf_dma; } ;
struct mvs_info {int /*<<< orphan*/  dma_pool; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
#define  SAS_PROTOCOL_SATA 131 
#define  SAS_PROTOCOL_SMP 130 
#define  SAS_PROTOCOL_SSP 129 
#define  SAS_PROTOCOL_STP 128 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mvs_slot_free (struct mvs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_protocol_ata (int) ; 

__attribute__((used)) static void mvs_slot_task_free(struct mvs_info *mvi, struct sas_task *task,
			  struct mvs_slot_info *slot, u32 slot_idx)
{
	if (!slot)
		return;
	if (!slot->task)
		return;
	if (!sas_protocol_ata(task->task_proto))
		if (slot->n_elem)
			dma_unmap_sg(mvi->dev, task->scatter,
				     slot->n_elem, task->data_dir);

	switch (task->task_proto) {
	case SAS_PROTOCOL_SMP:
		dma_unmap_sg(mvi->dev, &task->smp_task.smp_resp, 1,
			     DMA_FROM_DEVICE);
		dma_unmap_sg(mvi->dev, &task->smp_task.smp_req, 1,
			     DMA_TO_DEVICE);
		break;

	case SAS_PROTOCOL_SATA:
	case SAS_PROTOCOL_STP:
	case SAS_PROTOCOL_SSP:
	default:
		/* do nothing */
		break;
	}

	if (slot->buf) {
		dma_pool_free(mvi->dma_pool, slot->buf, slot->buf_dma);
		slot->buf = NULL;
	}
	list_del_init(&slot->entry);
	task->lldd_task = NULL;
	slot->task = NULL;
	slot->port = NULL;
	slot->slot_tag = 0xFFFFFFFF;
	mvs_slot_free(mvi, slot_idx);
}