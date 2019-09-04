#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int used_cnt; TYPE_2__* msix; scalar_t__ msix_cnt; } ;
struct qede_dev {TYPE_4__ int_info; int /*<<< orphan*/ * fp_array; int /*<<< orphan*/  cdev; TYPE_3__* ops; TYPE_1__* ndev; } ;
struct qed_common_ops {int (* get_fp_int ) (int /*<<< orphan*/ ,TYPE_4__*) ;int /*<<< orphan*/  (* simd_handler_config ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {struct qed_common_ops* common; } ;
struct TYPE_6__ {int /*<<< orphan*/  vector; } ;
struct TYPE_5__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int QEDE_QUEUE_CNT (struct qede_dev*) ; 
 int qede_req_msix_irqs (struct qede_dev*) ; 
 int /*<<< orphan*/  qede_simd_fp_handler ; 
 int stub1 (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qede_setup_irqs(struct qede_dev *edev)
{
	int i, rc = 0;

	/* Learn Interrupt configuration */
	rc = edev->ops->common->get_fp_int(edev->cdev, &edev->int_info);
	if (rc)
		return rc;

	if (edev->int_info.msix_cnt) {
		rc = qede_req_msix_irqs(edev);
		if (rc)
			return rc;
		edev->ndev->irq = edev->int_info.msix[0].vector;
	} else {
		const struct qed_common_ops *ops;

		/* qed should learn receive the RSS ids and callbacks */
		ops = edev->ops->common;
		for (i = 0; i < QEDE_QUEUE_CNT(edev); i++)
			ops->simd_handler_config(edev->cdev,
						 &edev->fp_array[i], i,
						 qede_simd_fp_handler);
		edev->int_info.used_cnt = QEDE_QUEUE_CNT(edev);
	}
	return 0;
}