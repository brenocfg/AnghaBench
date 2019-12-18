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
struct qedi_ctx {TYPE_2__ int_info; int /*<<< orphan*/  cdev; int /*<<< orphan*/  dbg_ctx; } ;
struct TYPE_6__ {TYPE_1__* common; } ;
struct TYPE_4__ {int (* set_fp_int ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* get_fp_int ) (int /*<<< orphan*/ ,TYPE_2__*) ;int /*<<< orphan*/  (* simd_handler_config ) (int /*<<< orphan*/ ,struct qedi_ctx**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  QEDI_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QEDI_LOG_DISC ; 
 int /*<<< orphan*/  QEDI_SIMD_HANDLER_NUM ; 
 int /*<<< orphan*/  num_online_cpus () ; 
 TYPE_3__* qedi_ops ; 
 int qedi_request_msix_irq (struct qedi_ctx*) ; 
 int /*<<< orphan*/  qedi_simd_int_handler ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,struct qedi_ctx**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qedi_setup_int(struct qedi_ctx *qedi)
{
	int rc = 0;

	rc = qedi_ops->common->set_fp_int(qedi->cdev, num_online_cpus());
	rc = qedi_ops->common->get_fp_int(qedi->cdev, &qedi->int_info);
	if (rc)
		goto exit_setup_int;

	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_DISC,
		  "Number of msix_cnt = 0x%x num of cpus = 0x%x\n",
		   qedi->int_info.msix_cnt, num_online_cpus());

	if (qedi->int_info.msix_cnt) {
		rc = qedi_request_msix_irq(qedi);
		goto exit_setup_int;
	} else {
		qedi_ops->common->simd_handler_config(qedi->cdev, &qedi,
						      QEDI_SIMD_HANDLER_NUM,
						      qedi_simd_int_handler);
		qedi->int_info.used_cnt = 1;
	}

exit_setup_int:
	return rc;
}