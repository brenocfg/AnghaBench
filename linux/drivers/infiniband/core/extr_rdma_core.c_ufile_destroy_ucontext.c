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
struct ib_uverbs_file {struct ib_ucontext* ucontext; } ;
struct ib_ucontext {int /*<<< orphan*/  res; int /*<<< orphan*/  cg_obj; struct ib_device* device; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dealloc_ucontext ) (struct ib_ucontext*) ;int /*<<< orphan*/  (* disassociate_ucontext ) (struct ib_ucontext*) ;} ;
struct ib_device {TYPE_1__ ops; } ;
typedef  enum rdma_remove_reason { ____Placeholder_rdma_remove_reason } rdma_remove_reason ;

/* Variables and functions */
 int /*<<< orphan*/  RDMACG_RESOURCE_HCA_HANDLE ; 
 int RDMA_REMOVE_DRIVER_REMOVE ; 
 int /*<<< orphan*/  ib_rdmacg_uncharge (int /*<<< orphan*/ *,struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ib_ucontext*) ; 
 int /*<<< orphan*/  rdma_restrack_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ib_ucontext*) ; 
 int /*<<< orphan*/  stub2 (struct ib_ucontext*) ; 
 int /*<<< orphan*/  uverbs_user_mmap_disassociate (struct ib_uverbs_file*) ; 

__attribute__((used)) static void ufile_destroy_ucontext(struct ib_uverbs_file *ufile,
				   enum rdma_remove_reason reason)
{
	struct ib_ucontext *ucontext = ufile->ucontext;
	struct ib_device *ib_dev = ucontext->device;

	/*
	 * If we are closing the FD then the user mmap VMAs must have
	 * already been destroyed as they hold on to the filep, otherwise
	 * they need to be zap'd.
	 */
	if (reason == RDMA_REMOVE_DRIVER_REMOVE) {
		uverbs_user_mmap_disassociate(ufile);
		if (ib_dev->ops.disassociate_ucontext)
			ib_dev->ops.disassociate_ucontext(ucontext);
	}

	ib_rdmacg_uncharge(&ucontext->cg_obj, ib_dev,
			   RDMACG_RESOURCE_HCA_HANDLE);

	rdma_restrack_del(&ucontext->res);

	ib_dev->ops.dealloc_ucontext(ucontext);
	kfree(ucontext);

	ufile->ucontext = NULL;
}