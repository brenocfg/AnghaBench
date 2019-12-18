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
typedef  int u32 ;
struct ib_udata {int dummy; } ;
struct ib_pd {int /*<<< orphan*/  usecnt; } ;
struct ib_gid_attr {int dummy; } ;
struct ib_ah {TYPE_2__* device; struct ib_pd* pd; struct ib_gid_attr* sgid_attr; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* destroy_ah ) (struct ib_ah*,int) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int RDMA_DESTROY_AH_SLEEPABLE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ib_ah*) ; 
 int /*<<< orphan*/  might_sleep_if (int) ; 
 int /*<<< orphan*/  rdma_put_gid_attr (struct ib_gid_attr const*) ; 
 int /*<<< orphan*/  stub1 (struct ib_ah*,int) ; 

int rdma_destroy_ah_user(struct ib_ah *ah, u32 flags, struct ib_udata *udata)
{
	const struct ib_gid_attr *sgid_attr = ah->sgid_attr;
	struct ib_pd *pd;

	might_sleep_if(flags & RDMA_DESTROY_AH_SLEEPABLE);

	pd = ah->pd;

	ah->device->ops.destroy_ah(ah, flags);
	atomic_dec(&pd->usecnt);
	if (sgid_attr)
		rdma_put_gid_attr(sgid_attr);

	kfree(ah);
	return 0;
}