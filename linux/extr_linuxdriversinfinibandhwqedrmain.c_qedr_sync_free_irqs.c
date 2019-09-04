#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int used_cnt; TYPE_2__* msix; scalar_t__ msix_cnt; } ;
struct qedr_dev {int num_hwfns; TYPE_1__ int_info; int /*<<< orphan*/ * cnq_array; } ;
struct TYPE_4__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qedr_sync_free_irqs(struct qedr_dev *dev)
{
	u32 vector;
	int i;

	for (i = 0; i < dev->int_info.used_cnt; i++) {
		if (dev->int_info.msix_cnt) {
			vector = dev->int_info.msix[i * dev->num_hwfns].vector;
			synchronize_irq(vector);
			free_irq(vector, &dev->cnq_array[i]);
		}
	}

	dev->int_info.used_cnt = 0;
}