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
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
struct qed_hwfn {size_t my_id; struct qed_dev* cdev; } ;
struct TYPE_5__ {scalar_t__ int_mode; } ;
struct TYPE_7__ {TYPE_2__* msix_table; TYPE_1__ out; } ;
struct qed_dev {TYPE_4__* pdev; TYPE_3__ int_params; } ;
struct TYPE_8__ {int /*<<< orphan*/  irq; } ;
struct TYPE_6__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 scalar_t__ QED_INT_MODE_MSIX ; 
 int /*<<< orphan*/  qed_slowpath_tasklet_flush (struct qed_hwfn*) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

void qed_slowpath_irq_sync(struct qed_hwfn *p_hwfn)
{
	struct qed_dev *cdev = p_hwfn->cdev;
	u8 id = p_hwfn->my_id;
	u32 int_mode;

	int_mode = cdev->int_params.out.int_mode;
	if (int_mode == QED_INT_MODE_MSIX)
		synchronize_irq(cdev->int_params.msix_table[id].vector);
	else
		synchronize_irq(cdev->pdev->irq);

	qed_slowpath_tasklet_flush(p_hwfn);
}