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
typedef  int u16 ;
struct TYPE_3__ {int sw_prod_idx; int /*<<< orphan*/ ** kcq; } ;
struct TYPE_4__ {int /*<<< orphan*/ * gen; } ;
struct cnic_local {int /*<<< orphan*/  cnic_irq_task; TYPE_1__ kcq1; TYPE_2__ status_blk; } ;
struct cnic_dev {int /*<<< orphan*/  flags; struct cnic_local* cnic_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNIC_F_CNIC_UP ; 
 size_t KCQ_IDX (int) ; 
 size_t KCQ_PG (int) ; 
 int MAX_KCQ_IDX ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cnic_doirq(struct cnic_dev *dev)
{
	struct cnic_local *cp = dev->cnic_priv;

	if (likely(test_bit(CNIC_F_CNIC_UP, &dev->flags))) {
		u16 prod = cp->kcq1.sw_prod_idx & MAX_KCQ_IDX;

		prefetch(cp->status_blk.gen);
		prefetch(&cp->kcq1.kcq[KCQ_PG(prod)][KCQ_IDX(prod)]);

		tasklet_schedule(&cp->cnic_irq_task);
	}
}