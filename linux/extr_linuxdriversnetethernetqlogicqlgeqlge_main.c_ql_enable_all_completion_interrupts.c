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
struct ql_adapter {int intr_count; TYPE_1__* intr_context; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  QL_MSIX_ENABLED ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ql_enable_completion_interrupt (struct ql_adapter*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ql_enable_all_completion_interrupts(struct ql_adapter *qdev)
{
	int i;
	for (i = 0; i < qdev->intr_count; i++) {
		/* The enable call does a atomic_dec_and_test
		 * and enables only if the result is zero.
		 * So we precharge it here.
		 */
		if (unlikely(!test_bit(QL_MSIX_ENABLED, &qdev->flags) ||
			i == 0))
			atomic_set(&qdev->intr_context[i].irq_cnt, 1);
		ql_enable_completion_interrupt(qdev, i);
	}

}