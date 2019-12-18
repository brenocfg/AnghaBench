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
struct TYPE_5__ {int used_cnt; scalar_t__ msix_cnt; } ;
struct qedf_ctx {int /*<<< orphan*/  dbg_ctx; TYPE_2__ int_info; int /*<<< orphan*/  cdev; } ;
struct TYPE_6__ {TYPE_1__* common; } ;
struct TYPE_4__ {int (* set_fp_int ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* get_fp_int ) (int /*<<< orphan*/ ,TYPE_2__*) ;int /*<<< orphan*/  (* simd_handler_config ) (int /*<<< orphan*/ ,struct qedf_ctx**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QEDF_LOG_DISC ; 
 int /*<<< orphan*/  QEDF_SIMD_HANDLER_NUM ; 
 int /*<<< orphan*/  num_online_cpus () ; 
 TYPE_3__* qed_ops ; 
 int qedf_request_msix_irq (struct qedf_ctx*) ; 
 int /*<<< orphan*/  qedf_simd_int_handler ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,struct qedf_ctx**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qedf_setup_int(struct qedf_ctx *qedf)
{
	int rc = 0;

	/*
	 * Learn interrupt configuration
	 */
	rc = qed_ops->common->set_fp_int(qedf->cdev, num_online_cpus());
	if (rc <= 0)
		return 0;

	rc  = qed_ops->common->get_fp_int(qedf->cdev, &qedf->int_info);
	if (rc)
		return 0;

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC, "Number of msix_cnt = "
		   "0x%x num of cpus = 0x%x\n", qedf->int_info.msix_cnt,
		   num_online_cpus());

	if (qedf->int_info.msix_cnt)
		return qedf_request_msix_irq(qedf);

	qed_ops->common->simd_handler_config(qedf->cdev, &qedf,
	    QEDF_SIMD_HANDLER_NUM, qedf_simd_int_handler);
	qedf->int_info.used_cnt = 1;

	QEDF_ERR(&qedf->dbg_ctx,
		 "Cannot load driver due to a lack of MSI-X vectors.\n");
	return -EINVAL;
}