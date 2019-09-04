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
struct qm_fd {int dummy; } ;
struct device {int dummy; } ;
struct caam_drv_req {TYPE_1__* drv_ctx; int /*<<< orphan*/ * fd_sgt; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  req_fq; } ;

/* Variables and functions */
 int CAAM_QI_ENQUEUE_RETRIES ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int EBUSY ; 
 int EIO ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  qm_fd_addr_set64 (struct qm_fd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_fd_clear_fd (struct qm_fd*) ; 
 int /*<<< orphan*/  qm_fd_set_compound (struct qm_fd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_sg_entry_get_len (int /*<<< orphan*/ *) ; 
 int qman_enqueue (int /*<<< orphan*/ ,struct qm_fd*) ; 

int caam_qi_enqueue(struct device *qidev, struct caam_drv_req *req)
{
	struct qm_fd fd;
	dma_addr_t addr;
	int ret;
	int num_retries = 0;

	qm_fd_clear_fd(&fd);
	qm_fd_set_compound(&fd, qm_sg_entry_get_len(&req->fd_sgt[1]));

	addr = dma_map_single(qidev, req->fd_sgt, sizeof(req->fd_sgt),
			      DMA_BIDIRECTIONAL);
	if (dma_mapping_error(qidev, addr)) {
		dev_err(qidev, "DMA mapping error for QI enqueue request\n");
		return -EIO;
	}
	qm_fd_addr_set64(&fd, addr);

	do {
		ret = qman_enqueue(req->drv_ctx->req_fq, &fd);
		if (likely(!ret))
			return 0;

		if (ret != -EBUSY)
			break;
		num_retries++;
	} while (num_retries < CAAM_QI_ENQUEUE_RETRIES);

	dev_err(qidev, "qman_enqueue failed: %d\n", ret);

	return ret;
}