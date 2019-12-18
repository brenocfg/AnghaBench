#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vnic_wq_buf {int /*<<< orphan*/  len; int /*<<< orphan*/  dma_addr; struct snic_host_req* os_buf; } ;
struct vnic_wq {int /*<<< orphan*/  vdev; } ;
struct TYPE_5__ {int /*<<< orphan*/ * next; } ;
struct snic_req_info {scalar_t__ sge_va; TYPE_2__ list; } ;
struct snic_host_req {int dummy; } ;
struct snic {int /*<<< orphan*/  shost; int /*<<< orphan*/  spl_cmd_lock; TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  SNIC_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SNIC_HOST_INFO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  list_del_init (TYPE_2__*) ; 
 scalar_t__ list_empty (TYPE_2__*) ; 
 struct snic_req_info* req_to_rqi (struct snic_host_req*) ; 
 int /*<<< orphan*/  snic_pci_unmap_rsp_buf (struct snic*,struct snic_req_info*) ; 
 int /*<<< orphan*/  snic_req_free (struct snic*,struct snic_req_info*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct snic* svnic_dev_priv (int /*<<< orphan*/ ) ; 

void
snic_free_wq_buf(struct vnic_wq *wq, struct vnic_wq_buf *buf)
{

	struct snic_host_req *req = buf->os_buf;
	struct snic *snic = svnic_dev_priv(wq->vdev);
	struct snic_req_info *rqi = NULL;
	unsigned long flags;

	dma_unmap_single(&snic->pdev->dev, buf->dma_addr, buf->len,
			 DMA_TO_DEVICE);

	rqi = req_to_rqi(req);
	spin_lock_irqsave(&snic->spl_cmd_lock, flags);
	if (list_empty(&rqi->list)) {
		spin_unlock_irqrestore(&snic->spl_cmd_lock, flags);
		goto end;
	}

	SNIC_BUG_ON(rqi->list.next == NULL); /* if not added to spl_cmd_list */
	list_del_init(&rqi->list);
	spin_unlock_irqrestore(&snic->spl_cmd_lock, flags);

	if (rqi->sge_va) {
		snic_pci_unmap_rsp_buf(snic, rqi);
		kfree((void *)rqi->sge_va);
		rqi->sge_va = 0;
	}
	snic_req_free(snic, rqi);
	SNIC_HOST_INFO(snic->shost, "snic_free_wq_buf .. freed.\n");

end:
	return;
}