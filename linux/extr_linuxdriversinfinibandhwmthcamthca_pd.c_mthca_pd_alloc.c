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
struct mthca_pd {int privileged; int pd_num; int /*<<< orphan*/  ntmr; int /*<<< orphan*/  sqp_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  alloc; } ;
struct mthca_dev {TYPE_1__ pd_table; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MTHCA_MPT_FLAG_LOCAL_READ ; 
 int MTHCA_MPT_FLAG_LOCAL_WRITE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mthca_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mthca_free (int /*<<< orphan*/ *,int) ; 
 int mthca_mr_alloc_notrans (struct mthca_dev*,int,int,int /*<<< orphan*/ *) ; 

int mthca_pd_alloc(struct mthca_dev *dev, int privileged, struct mthca_pd *pd)
{
	int err = 0;

	pd->privileged = privileged;

	atomic_set(&pd->sqp_count, 0);
	pd->pd_num = mthca_alloc(&dev->pd_table.alloc);
	if (pd->pd_num == -1)
		return -ENOMEM;

	if (privileged) {
		err = mthca_mr_alloc_notrans(dev, pd->pd_num,
					     MTHCA_MPT_FLAG_LOCAL_READ |
					     MTHCA_MPT_FLAG_LOCAL_WRITE,
					     &pd->ntmr);
		if (err)
			mthca_free(&dev->pd_table.alloc, pd->pd_num);
	}

	return err;
}