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
struct TYPE_3__ {int /*<<< orphan*/  alloc; TYPE_2__* eq; } ;
struct mthca_dev {TYPE_1__ eq_table; } ;
struct TYPE_4__ {int /*<<< orphan*/  eqn; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTHCA_CMD_EVENT_MASK ; 
 size_t MTHCA_EQ_ASYNC ; 
 size_t MTHCA_EQ_CMD ; 
 int MTHCA_NUM_EQ ; 
 int /*<<< orphan*/  async_mask (struct mthca_dev*) ; 
 int /*<<< orphan*/  mthca_MAP_EQ (struct mthca_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_alloc_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mthca_free_eq (struct mthca_dev*,TYPE_2__*) ; 
 int /*<<< orphan*/  mthca_free_irqs (struct mthca_dev*) ; 
 int /*<<< orphan*/  mthca_unmap_eq_regs (struct mthca_dev*) ; 

void mthca_cleanup_eq_table(struct mthca_dev *dev)
{
	int i;

	mthca_free_irqs(dev);

	mthca_MAP_EQ(dev, async_mask(dev),
		     1, dev->eq_table.eq[MTHCA_EQ_ASYNC].eqn);
	mthca_MAP_EQ(dev, MTHCA_CMD_EVENT_MASK,
		     1, dev->eq_table.eq[MTHCA_EQ_CMD].eqn);

	for (i = 0; i < MTHCA_NUM_EQ; ++i)
		mthca_free_eq(dev, &dev->eq_table.eq[i]);

	mthca_unmap_eq_regs(dev);

	mthca_alloc_cleanup(&dev->eq_table.alloc);
}