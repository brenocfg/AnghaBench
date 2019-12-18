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
struct ib_umem {TYPE_1__* owning_mm; int /*<<< orphan*/  ibdev; scalar_t__ is_odp; } ;
struct TYPE_2__ {int /*<<< orphan*/  pinned_vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ib_umem_release (int /*<<< orphan*/ ,struct ib_umem*,int) ; 
 int /*<<< orphan*/  atomic64_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_umem_num_pages (struct ib_umem*) ; 
 void ib_umem_odp_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ib_umem*) ; 
 int /*<<< orphan*/  mmdrop (TYPE_1__*) ; 
 int /*<<< orphan*/  to_ib_umem_odp (struct ib_umem*) ; 

void ib_umem_release(struct ib_umem *umem)
{
	if (!umem)
		return;
	if (umem->is_odp)
		return ib_umem_odp_release(to_ib_umem_odp(umem));

	__ib_umem_release(umem->ibdev, umem, 1);

	atomic64_sub(ib_umem_num_pages(umem), &umem->owning_mm->pinned_vm);
	mmdrop(umem->owning_mm);
	kfree(umem);
}