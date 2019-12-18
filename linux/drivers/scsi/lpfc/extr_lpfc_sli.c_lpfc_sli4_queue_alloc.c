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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct lpfc_queue {int page_count; void** q_pgs; int entry_cnt_per_pg; int entry_size; int entry_count; int page_size; int /*<<< orphan*/  sched_spwork; int /*<<< orphan*/  sched_irqwork; int /*<<< orphan*/  spwork; int /*<<< orphan*/  irqwork; int /*<<< orphan*/  page_list; struct lpfc_hba* phba; int /*<<< orphan*/  cpu_list; int /*<<< orphan*/  child_list; int /*<<< orphan*/  wqfull_list; int /*<<< orphan*/  wq_list; int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int if_page_sz; int wqpcnt; int /*<<< orphan*/  supported; } ;
struct TYPE_5__ {TYPE_1__ pc_sli4_params; } ;
struct lpfc_hba {TYPE_3__* pcidev; TYPE_2__ sli4_hba; } ;
struct lpfc_dmabuf {void* virt; int buffer_tag; int /*<<< orphan*/  list; int /*<<< orphan*/  phys; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_node (int) ; 
 int /*<<< orphan*/  dev_to_node (int /*<<< orphan*/ *) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct lpfc_dmabuf*) ; 
 void* kzalloc_node (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_sli4_dly_hba_process_cq ; 
 int /*<<< orphan*/  lpfc_sli4_dly_sp_process_cq ; 
 int /*<<< orphan*/  lpfc_sli4_hba_process_cq ; 
 int /*<<< orphan*/  lpfc_sli4_queue_free (struct lpfc_queue*) ; 
 int /*<<< orphan*/  lpfc_sli4_sp_process_cq ; 

struct lpfc_queue *
lpfc_sli4_queue_alloc(struct lpfc_hba *phba, uint32_t page_size,
		      uint32_t entry_size, uint32_t entry_count, int cpu)
{
	struct lpfc_queue *queue;
	struct lpfc_dmabuf *dmabuf;
	uint32_t hw_page_size = phba->sli4_hba.pc_sli4_params.if_page_sz;
	uint16_t x, pgcnt;

	if (!phba->sli4_hba.pc_sli4_params.supported)
		hw_page_size = page_size;

	pgcnt = ALIGN(entry_size * entry_count, hw_page_size) / hw_page_size;

	/* If needed, Adjust page count to match the max the adapter supports */
	if (pgcnt > phba->sli4_hba.pc_sli4_params.wqpcnt)
		pgcnt = phba->sli4_hba.pc_sli4_params.wqpcnt;

	queue = kzalloc_node(sizeof(*queue) + (sizeof(void *) * pgcnt),
			     GFP_KERNEL, cpu_to_node(cpu));
	if (!queue)
		return NULL;

	INIT_LIST_HEAD(&queue->list);
	INIT_LIST_HEAD(&queue->wq_list);
	INIT_LIST_HEAD(&queue->wqfull_list);
	INIT_LIST_HEAD(&queue->page_list);
	INIT_LIST_HEAD(&queue->child_list);
	INIT_LIST_HEAD(&queue->cpu_list);

	/* Set queue parameters now.  If the system cannot provide memory
	 * resources, the free routine needs to know what was allocated.
	 */
	queue->page_count = pgcnt;
	queue->q_pgs = (void **)&queue[1];
	queue->entry_cnt_per_pg = hw_page_size / entry_size;
	queue->entry_size = entry_size;
	queue->entry_count = entry_count;
	queue->page_size = hw_page_size;
	queue->phba = phba;

	for (x = 0; x < queue->page_count; x++) {
		dmabuf = kzalloc_node(sizeof(*dmabuf), GFP_KERNEL,
				      dev_to_node(&phba->pcidev->dev));
		if (!dmabuf)
			goto out_fail;
		dmabuf->virt = dma_alloc_coherent(&phba->pcidev->dev,
						  hw_page_size, &dmabuf->phys,
						  GFP_KERNEL);
		if (!dmabuf->virt) {
			kfree(dmabuf);
			goto out_fail;
		}
		dmabuf->buffer_tag = x;
		list_add_tail(&dmabuf->list, &queue->page_list);
		/* use lpfc_sli4_qe to index a paritcular entry in this page */
		queue->q_pgs[x] = dmabuf->virt;
	}
	INIT_WORK(&queue->irqwork, lpfc_sli4_hba_process_cq);
	INIT_WORK(&queue->spwork, lpfc_sli4_sp_process_cq);
	INIT_DELAYED_WORK(&queue->sched_irqwork, lpfc_sli4_dly_hba_process_cq);
	INIT_DELAYED_WORK(&queue->sched_spwork, lpfc_sli4_dly_sp_process_cq);

	/* notify_interval will be set during q creation */

	return queue;
out_fail:
	lpfc_sli4_queue_free(queue);
	return NULL;
}