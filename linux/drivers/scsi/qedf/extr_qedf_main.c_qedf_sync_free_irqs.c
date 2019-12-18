#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct TYPE_10__ {int used_cnt; TYPE_3__* msix; scalar_t__ msix_cnt; } ;
struct TYPE_7__ {int num_hwfns; } ;
struct TYPE_8__ {TYPE_1__ common; } ;
struct qedf_ctx {int /*<<< orphan*/  cdev; TYPE_4__ int_info; int /*<<< orphan*/ * fp_array; int /*<<< orphan*/  dbg_ctx; TYPE_2__ dev_info; } ;
struct TYPE_12__ {TYPE_5__* common; } ;
struct TYPE_11__ {size_t (* get_affin_hwfn_idx ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_fp_int ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* simd_handler_clean ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,size_t) ; 
 int /*<<< orphan*/  QEDF_LOG_DISC ; 
 int /*<<< orphan*/  QEDF_SIMD_HANDLER_NUM ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_affinity_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_6__* qed_ops ; 
 size_t stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qedf_sync_free_irqs(struct qedf_ctx *qedf)
{
	int i;
	u16 vector_idx = 0;
	u32 vector;

	if (qedf->int_info.msix_cnt) {
		for (i = 0; i < qedf->int_info.used_cnt; i++) {
			vector_idx = i * qedf->dev_info.common.num_hwfns +
				qed_ops->common->get_affin_hwfn_idx(qedf->cdev);
			QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_DISC,
				  "Freeing IRQ #%d vector_idx=%d.\n",
				  i, vector_idx);
			vector = qedf->int_info.msix[vector_idx].vector;
			synchronize_irq(vector);
			irq_set_affinity_hint(vector, NULL);
			irq_set_affinity_notifier(vector, NULL);
			free_irq(vector, &qedf->fp_array[i]);
		}
	} else
		qed_ops->common->simd_handler_clean(qedf->cdev,
		    QEDF_SIMD_HANDLER_NUM);

	qedf->int_info.used_cnt = 0;
	qed_ops->common->set_fp_int(qedf->cdev, 0);
}