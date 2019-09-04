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
struct ib_ucontext {TYPE_1__* device; int /*<<< orphan*/  cg_obj; int /*<<< orphan*/  tgid; } ;
typedef  enum rdma_remove_reason { ____Placeholder_rdma_remove_reason } rdma_remove_reason ;
struct TYPE_2__ {int (* dealloc_ucontext ) (struct ib_ucontext*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RDMACG_RESOURCE_HCA_HANDLE ; 
 int RDMA_REMOVE_DRIVER_REMOVE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ib_rdmacg_uncharge (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 
 int stub1 (struct ib_ucontext*) ; 
 int /*<<< orphan*/  ufile_disassociate_ucontext (struct ib_ucontext*) ; 

__attribute__((used)) static void ufile_destroy_ucontext(struct ib_uverbs_file *ufile,
				   enum rdma_remove_reason reason)
{
	struct ib_ucontext *ucontext = ufile->ucontext;
	int ret;

	if (reason == RDMA_REMOVE_DRIVER_REMOVE)
		ufile_disassociate_ucontext(ucontext);

	put_pid(ucontext->tgid);
	ib_rdmacg_uncharge(&ucontext->cg_obj, ucontext->device,
			   RDMACG_RESOURCE_HCA_HANDLE);

	/*
	 * FIXME: Drivers are not permitted to fail dealloc_ucontext, remove
	 * the error return.
	 */
	ret = ucontext->device->dealloc_ucontext(ucontext);
	WARN_ON(ret);

	ufile->ucontext = NULL;
}