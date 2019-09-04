#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  arm_mask; TYPE_2__* eq; int /*<<< orphan*/  clr_int; scalar_t__ clr_mask; } ;
struct mthca_dev {TYPE_1__ eq_table; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_5__ {int /*<<< orphan*/  cons_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int MTHCA_NUM_EQ ; 
 int /*<<< orphan*/  arbel_eq_req_not (struct mthca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arbel_set_eq_ci (struct mthca_dev*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mthca_eq_int (struct mthca_dev*,TYPE_2__*) ; 
 int /*<<< orphan*/  writel (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t mthca_arbel_interrupt(int irq, void *dev_ptr)
{
	struct mthca_dev *dev = dev_ptr;
	int work = 0;
	int i;

	if (dev->eq_table.clr_mask)
		writel(dev->eq_table.clr_mask, dev->eq_table.clr_int);

	for (i = 0; i < MTHCA_NUM_EQ; ++i)
		if (mthca_eq_int(dev, &dev->eq_table.eq[i])) {
			work = 1;
			arbel_set_eq_ci(dev, &dev->eq_table.eq[i],
					dev->eq_table.eq[i].cons_index);
		}

	arbel_eq_req_not(dev, dev->eq_table.arm_mask);

	return IRQ_RETVAL(work);
}