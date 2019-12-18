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
struct ql_adapter {int /*<<< orphan*/  ide_completion; int /*<<< orphan*/  ndev; struct mbox_params idc_mbc; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int ql_get_mb_sts (struct ql_adapter*,struct mbox_params*) ; 
 int /*<<< orphan*/  ql_queue_fw_error (struct ql_adapter*) ; 

__attribute__((used)) static int ql_idc_cmplt_aen(struct ql_adapter *qdev)
{
	int status;
	struct mbox_params *mbcp = &qdev->idc_mbc;
	mbcp->out_count = 4;
	status = ql_get_mb_sts(qdev, mbcp);
	if (status) {
		netif_err(qdev, drv, qdev->ndev,
			  "Could not read MPI, resetting RISC!\n");
		ql_queue_fw_error(qdev);
	} else
		/* Wake up the sleeping mpi_idc_work thread that is
		 * waiting for this event.
		 */
		complete(&qdev->ide_completion);

	return status;
}