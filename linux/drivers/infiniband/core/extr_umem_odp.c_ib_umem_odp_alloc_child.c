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
struct ib_umem {size_t length; unsigned long address; int /*<<< orphan*/  owning_mm; int /*<<< orphan*/  writable; int /*<<< orphan*/  ibdev; } ;
struct ib_umem_odp {int /*<<< orphan*/  page_shift; struct ib_umem umem; int /*<<< orphan*/  is_implicit_odp; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct ib_umem_odp* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SHIFT ; 
 scalar_t__ WARN_ON (int) ; 
 int ib_init_umem_odp (struct ib_umem_odp*) ; 
 int /*<<< orphan*/  kfree (struct ib_umem_odp*) ; 
 struct ib_umem_odp* kzalloc (int,int /*<<< orphan*/ ) ; 

struct ib_umem_odp *ib_umem_odp_alloc_child(struct ib_umem_odp *root,
					    unsigned long addr, size_t size)
{
	/*
	 * Caller must ensure that root cannot be freed during the call to
	 * ib_alloc_odp_umem.
	 */
	struct ib_umem_odp *odp_data;
	struct ib_umem *umem;
	int ret;

	if (WARN_ON(!root->is_implicit_odp))
		return ERR_PTR(-EINVAL);

	odp_data = kzalloc(sizeof(*odp_data), GFP_KERNEL);
	if (!odp_data)
		return ERR_PTR(-ENOMEM);
	umem = &odp_data->umem;
	umem->ibdev = root->umem.ibdev;
	umem->length     = size;
	umem->address    = addr;
	umem->writable   = root->umem.writable;
	umem->owning_mm  = root->umem.owning_mm;
	odp_data->page_shift = PAGE_SHIFT;

	ret = ib_init_umem_odp(odp_data);
	if (ret) {
		kfree(odp_data);
		return ERR_PTR(ret);
	}
	return odp_data;
}