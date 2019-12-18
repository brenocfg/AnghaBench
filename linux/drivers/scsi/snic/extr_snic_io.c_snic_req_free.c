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
struct snic_req_info {scalar_t__ sge_va; int req_len; size_t rq_pool_type; scalar_t__ req_pa; struct snic_req_info* req; struct snic_req_info* dr_req; struct snic_req_info* abort_req; } ;
struct snic_host_req {int dummy; } ;
struct snic {int /*<<< orphan*/ * req_pool; TYPE_1__* pdev; int /*<<< orphan*/  shost; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  SNIC_BUG_ON (int) ; 
 size_t SNIC_REQ_TM_CACHE ; 
 int /*<<< orphan*/  SNIC_SCSI_DBG (int /*<<< orphan*/ ,char*,struct snic_req_info*,struct snic_req_info*,struct snic_req_info*,struct snic_req_info*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct snic_req_info*,int /*<<< orphan*/ ) ; 

void
snic_req_free(struct snic *snic, struct snic_req_info *rqi)
{
	SNIC_BUG_ON(rqi->req == rqi->abort_req);
	SNIC_BUG_ON(rqi->req == rqi->dr_req);
	SNIC_BUG_ON(rqi->sge_va != 0);

	SNIC_SCSI_DBG(snic->shost,
		      "Req_free:rqi %p:ioreq %p:abt %p:dr %p\n",
		      rqi, rqi->req, rqi->abort_req, rqi->dr_req);

	if (rqi->abort_req) {
		if (rqi->abort_req->req_pa)
			dma_unmap_single(&snic->pdev->dev,
					 rqi->abort_req->req_pa,
					 sizeof(struct snic_host_req),
					 DMA_TO_DEVICE);

		mempool_free(rqi->abort_req, snic->req_pool[SNIC_REQ_TM_CACHE]);
	}

	if (rqi->dr_req) {
		if (rqi->dr_req->req_pa)
			dma_unmap_single(&snic->pdev->dev,
					 rqi->dr_req->req_pa,
					 sizeof(struct snic_host_req),
					 DMA_TO_DEVICE);

		mempool_free(rqi->dr_req, snic->req_pool[SNIC_REQ_TM_CACHE]);
	}

	if (rqi->req->req_pa)
		dma_unmap_single(&snic->pdev->dev,
				 rqi->req->req_pa,
				 rqi->req_len,
				 DMA_TO_DEVICE);

	mempool_free(rqi, snic->req_pool[rqi->rq_pool_type]);
}