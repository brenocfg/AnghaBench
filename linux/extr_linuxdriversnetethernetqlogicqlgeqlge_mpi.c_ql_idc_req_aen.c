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
struct mbox_params {int out_count; } ;
struct ql_adapter {int /*<<< orphan*/  mpi_idc_work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  ndev; struct mbox_params idc_mbc; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTR_MASK ; 
 int INTR_MASK_PI ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int ql_get_mb_sts (struct ql_adapter*,struct mbox_params*) ; 
 int /*<<< orphan*/  ql_queue_asic_error (struct ql_adapter*) ; 
 int /*<<< orphan*/  ql_write32 (struct ql_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ql_idc_req_aen(struct ql_adapter *qdev)
{
	int status;
	struct mbox_params *mbcp = &qdev->idc_mbc;

	netif_err(qdev, drv, qdev->ndev, "Enter!\n");
	/* Get the status data and start up a thread to
	 * handle the request.
	 */
	mbcp->out_count = 4;
	status = ql_get_mb_sts(qdev, mbcp);
	if (status) {
		netif_err(qdev, drv, qdev->ndev,
			  "Could not read MPI, resetting ASIC!\n");
		ql_queue_asic_error(qdev);
	} else	{
		/* Begin polled mode early so
		 * we don't get another interrupt
		 * when we leave mpi_worker.
		 */
		ql_write32(qdev, INTR_MASK, (INTR_MASK_PI << 16));
		queue_delayed_work(qdev->workqueue, &qdev->mpi_idc_work, 0);
	}
	return status;
}