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
typedef  int u32 ;
struct rdma_ah_attr {int /*<<< orphan*/  type; } ;
struct ib_udata {int dummy; } ;
struct ib_pd {int /*<<< orphan*/  usecnt; struct ib_device* device; } ;
struct TYPE_2__ {int (* create_ah ) (struct ib_ah*,struct rdma_ah_attr*,int,struct ib_udata*) ;} ;
struct ib_device {TYPE_1__ ops; } ;
struct ib_ah {int /*<<< orphan*/  sgid_attr; int /*<<< orphan*/  type; struct ib_pd* pd; struct ib_device* device; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 struct ib_ah* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int RDMA_CREATE_AH_SLEEPABLE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_ah ; 
 int /*<<< orphan*/  kfree (struct ib_ah*) ; 
 int /*<<< orphan*/  might_sleep_if (int) ; 
 int /*<<< orphan*/  rdma_update_sgid_attr (struct rdma_ah_attr*,int /*<<< orphan*/ *) ; 
 struct ib_ah* rdma_zalloc_drv_obj_gfp (struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct ib_ah*,struct rdma_ah_attr*,int,struct ib_udata*) ; 

__attribute__((used)) static struct ib_ah *_rdma_create_ah(struct ib_pd *pd,
				     struct rdma_ah_attr *ah_attr,
				     u32 flags,
				     struct ib_udata *udata)
{
	struct ib_device *device = pd->device;
	struct ib_ah *ah;
	int ret;

	might_sleep_if(flags & RDMA_CREATE_AH_SLEEPABLE);

	if (!device->ops.create_ah)
		return ERR_PTR(-EOPNOTSUPP);

	ah = rdma_zalloc_drv_obj_gfp(
		device, ib_ah,
		(flags & RDMA_CREATE_AH_SLEEPABLE) ? GFP_KERNEL : GFP_ATOMIC);
	if (!ah)
		return ERR_PTR(-ENOMEM);

	ah->device = device;
	ah->pd = pd;
	ah->type = ah_attr->type;
	ah->sgid_attr = rdma_update_sgid_attr(ah_attr, NULL);

	ret = device->ops.create_ah(ah, ah_attr, flags, udata);
	if (ret) {
		kfree(ah);
		return ERR_PTR(ret);
	}

	atomic_inc(&pd->usecnt);
	return ah;
}