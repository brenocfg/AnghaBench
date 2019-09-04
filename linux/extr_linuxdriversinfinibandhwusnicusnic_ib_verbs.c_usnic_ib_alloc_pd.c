#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ib_pd {int dummy; } ;
struct usnic_ib_pd {struct ib_pd ibpd; void* umem_pd; } ;
struct ib_udata {int dummy; } ;
struct ib_ucontext {int dummy; } ;
struct ib_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct ib_pd* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR_OR_NULL (void*) ; 
 int /*<<< orphan*/  PTR_ERR (void*) ; 
 int /*<<< orphan*/  kfree (struct usnic_ib_pd*) ; 
 struct usnic_ib_pd* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usnic_dbg (char*) ; 
 int /*<<< orphan*/  usnic_info (char*,struct usnic_ib_pd*,struct ib_ucontext*,int /*<<< orphan*/ ) ; 
 void* usnic_uiom_alloc_pd () ; 

struct ib_pd *usnic_ib_alloc_pd(struct ib_device *ibdev,
					struct ib_ucontext *context,
					struct ib_udata *udata)
{
	struct usnic_ib_pd *pd;
	void *umem_pd;

	usnic_dbg("\n");

	pd = kzalloc(sizeof(*pd), GFP_KERNEL);
	if (!pd)
		return ERR_PTR(-ENOMEM);

	umem_pd = pd->umem_pd = usnic_uiom_alloc_pd();
	if (IS_ERR_OR_NULL(umem_pd)) {
		kfree(pd);
		return ERR_PTR(umem_pd ? PTR_ERR(umem_pd) : -ENOMEM);
	}

	usnic_info("domain 0x%p allocated for context 0x%p and device %s\n",
			pd, context, ibdev->name);
	return &pd->ibpd;
}