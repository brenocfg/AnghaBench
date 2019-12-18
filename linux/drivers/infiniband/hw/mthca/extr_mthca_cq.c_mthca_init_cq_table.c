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
struct TYPE_3__ {int /*<<< orphan*/  alloc; int /*<<< orphan*/  cq; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  num_cqs; int /*<<< orphan*/  reserved_cqs; } ;
struct mthca_dev {TYPE_1__ cq_table; TYPE_2__ limits; } ;

/* Variables and functions */
 int /*<<< orphan*/  mthca_alloc_cleanup (int /*<<< orphan*/ *) ; 
 int mthca_alloc_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int mthca_array_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int mthca_init_cq_table(struct mthca_dev *dev)
{
	int err;

	spin_lock_init(&dev->cq_table.lock);

	err = mthca_alloc_init(&dev->cq_table.alloc,
			       dev->limits.num_cqs,
			       (1 << 24) - 1,
			       dev->limits.reserved_cqs);
	if (err)
		return err;

	err = mthca_array_init(&dev->cq_table.cq,
			       dev->limits.num_cqs);
	if (err)
		mthca_alloc_cleanup(&dev->cq_table.alloc);

	return err;
}