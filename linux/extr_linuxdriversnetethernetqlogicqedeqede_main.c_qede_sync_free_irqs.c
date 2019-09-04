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
struct TYPE_8__ {int used_cnt; TYPE_1__* msix; scalar_t__ msix_cnt; } ;
struct qede_dev {TYPE_4__ int_info; int /*<<< orphan*/  cdev; TYPE_3__* ops; int /*<<< orphan*/ * fp_array; } ;
struct TYPE_7__ {TYPE_2__* common; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* simd_handler_clean ) (int /*<<< orphan*/ ,int) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qede_sync_free_irqs(struct qede_dev *edev)
{
	int i;

	for (i = 0; i < edev->int_info.used_cnt; i++) {
		if (edev->int_info.msix_cnt) {
			synchronize_irq(edev->int_info.msix[i].vector);
			free_irq(edev->int_info.msix[i].vector,
				 &edev->fp_array[i]);
		} else {
			edev->ops->common->simd_handler_clean(edev->cdev, i);
		}
	}

	edev->int_info.used_cnt = 0;
}