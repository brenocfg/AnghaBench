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
struct rdma_ah_attr {int /*<<< orphan*/  type; } ;
struct ib_udata {int dummy; } ;
struct ib_pd {int /*<<< orphan*/  usecnt; TYPE_1__* device; } ;
struct ib_ah {int /*<<< orphan*/  sgid_attr; int /*<<< orphan*/  type; int /*<<< orphan*/ * uobject; struct ib_pd* pd; TYPE_1__* device; } ;
struct TYPE_2__ {struct ib_ah* (* create_ah ) (struct ib_pd*,struct rdma_ah_attr*,struct ib_udata*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EOPNOTSUPP ; 
 struct ib_ah* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct ib_ah*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_update_sgid_attr (struct rdma_ah_attr*,int /*<<< orphan*/ *) ; 
 struct ib_ah* stub1 (struct ib_pd*,struct rdma_ah_attr*,struct ib_udata*) ; 

__attribute__((used)) static struct ib_ah *_rdma_create_ah(struct ib_pd *pd,
				     struct rdma_ah_attr *ah_attr,
				     struct ib_udata *udata)
{
	struct ib_ah *ah;

	if (!pd->device->create_ah)
		return ERR_PTR(-EOPNOTSUPP);

	ah = pd->device->create_ah(pd, ah_attr, udata);

	if (!IS_ERR(ah)) {
		ah->device  = pd->device;
		ah->pd      = pd;
		ah->uobject = NULL;
		ah->type    = ah_attr->type;
		ah->sgid_attr = rdma_update_sgid_attr(ah_attr, NULL);

		atomic_inc(&pd->usecnt);
	}

	return ah;
}