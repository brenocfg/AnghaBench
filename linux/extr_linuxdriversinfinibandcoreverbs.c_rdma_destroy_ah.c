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
struct ib_pd {int /*<<< orphan*/  usecnt; } ;
struct ib_gid_attr {int dummy; } ;
struct ib_ah {TYPE_1__* device; struct ib_pd* pd; struct ib_gid_attr* sgid_attr; } ;
struct TYPE_2__ {int (* destroy_ah ) (struct ib_ah*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_put_gid_attr (struct ib_gid_attr const*) ; 
 int stub1 (struct ib_ah*) ; 

int rdma_destroy_ah(struct ib_ah *ah)
{
	const struct ib_gid_attr *sgid_attr = ah->sgid_attr;
	struct ib_pd *pd;
	int ret;

	pd = ah->pd;
	ret = ah->device->destroy_ah(ah);
	if (!ret) {
		atomic_dec(&pd->usecnt);
		if (sgid_attr)
			rdma_put_gid_attr(sgid_attr);
	}

	return ret;
}