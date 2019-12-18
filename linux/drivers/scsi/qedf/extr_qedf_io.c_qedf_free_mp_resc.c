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
typedef  int uint64_t ;
struct scsi_sge {int dummy; } ;
struct qedf_mp_req {int /*<<< orphan*/ * resp_buf; int /*<<< orphan*/  resp_buf_dma; int /*<<< orphan*/ * req_buf; int /*<<< orphan*/  req_buf_dma; int /*<<< orphan*/ * mp_resp_bd; int /*<<< orphan*/  mp_resp_bd_dma; int /*<<< orphan*/ * mp_req_bd; int /*<<< orphan*/  mp_req_bd_dma; } ;
struct qedf_ioreq {TYPE_1__* fcport; struct qedf_mp_req mp_req; } ;
struct qedf_ctx {TYPE_2__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct qedf_ctx* qedf; } ;

/* Variables and functions */
 int QEDF_PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qedf_free_mp_resc(struct qedf_ioreq *io_req)
{
	struct qedf_mp_req *mp_req = &(io_req->mp_req);
	struct qedf_ctx *qedf = io_req->fcport->qedf;
	uint64_t sz = sizeof(struct scsi_sge);

	/* clear tm flags */
	if (mp_req->mp_req_bd) {
		dma_free_coherent(&qedf->pdev->dev, sz,
		    mp_req->mp_req_bd, mp_req->mp_req_bd_dma);
		mp_req->mp_req_bd = NULL;
	}
	if (mp_req->mp_resp_bd) {
		dma_free_coherent(&qedf->pdev->dev, sz,
		    mp_req->mp_resp_bd, mp_req->mp_resp_bd_dma);
		mp_req->mp_resp_bd = NULL;
	}
	if (mp_req->req_buf) {
		dma_free_coherent(&qedf->pdev->dev, QEDF_PAGE_SIZE,
		    mp_req->req_buf, mp_req->req_buf_dma);
		mp_req->req_buf = NULL;
	}
	if (mp_req->resp_buf) {
		dma_free_coherent(&qedf->pdev->dev, QEDF_PAGE_SIZE,
		    mp_req->resp_buf, mp_req->resp_buf_dma);
		mp_req->resp_buf = NULL;
	}
}