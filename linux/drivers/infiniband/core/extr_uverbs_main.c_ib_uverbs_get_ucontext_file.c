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
struct ib_uverbs_file {TYPE_1__* device; int /*<<< orphan*/  ucontext; } ;
struct ib_ucontext {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  disassociate_srcu; int /*<<< orphan*/  ib_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 struct ib_ucontext* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct ib_ucontext* smp_load_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_dereference (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct ib_ucontext *ib_uverbs_get_ucontext_file(struct ib_uverbs_file *ufile)
{
	/*
	 * We do not hold the hw_destroy_rwsem lock for this flow, instead
	 * srcu is used. It does not matter if someone races this with
	 * get_context, we get NULL or valid ucontext.
	 */
	struct ib_ucontext *ucontext = smp_load_acquire(&ufile->ucontext);

	if (!srcu_dereference(ufile->device->ib_dev,
			      &ufile->device->disassociate_srcu))
		return ERR_PTR(-EIO);

	if (!ucontext)
		return ERR_PTR(-EINVAL);

	return ucontext;
}