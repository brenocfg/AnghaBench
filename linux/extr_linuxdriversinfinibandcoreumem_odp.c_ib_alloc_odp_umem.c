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
struct ib_umem_odp {size_t length; unsigned long address; size_t page_shift; int writable; int mn_counters_active; void* page_list; struct ib_umem_odp* odp_data; int /*<<< orphan*/  no_private_counters; int /*<<< orphan*/  interval_tree; void* dma_list; int /*<<< orphan*/  notifier_completion; int /*<<< orphan*/  umem_mutex; struct ib_umem_odp* umem; struct ib_ucontext* context; } ;
struct ib_umem {size_t length; unsigned long address; size_t page_shift; int writable; int mn_counters_active; void* page_list; struct ib_umem* odp_data; int /*<<< orphan*/  no_private_counters; int /*<<< orphan*/  interval_tree; void* dma_list; int /*<<< orphan*/  notifier_completion; int /*<<< orphan*/  umem_mutex; struct ib_umem* umem; struct ib_ucontext* context; } ;
struct ib_ucontext {int /*<<< orphan*/  umem_rwsem; int /*<<< orphan*/  no_private_counters; int /*<<< orphan*/  notifier_count; int /*<<< orphan*/  umem_tree; int /*<<< orphan*/  odp_mrs_count; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct ib_umem_odp* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t PAGE_SHIFT ; 
 int /*<<< orphan*/  array_size (int,int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ib_umem_odp*) ; 
 struct ib_umem_odp* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbt_ib_umem_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (void*) ; 
 void* vzalloc (int /*<<< orphan*/ ) ; 

struct ib_umem *ib_alloc_odp_umem(struct ib_ucontext *context,
				  unsigned long addr,
				  size_t size)
{
	struct ib_umem *umem;
	struct ib_umem_odp *odp_data;
	int pages = size >> PAGE_SHIFT;
	int ret;

	umem = kzalloc(sizeof(*umem), GFP_KERNEL);
	if (!umem)
		return ERR_PTR(-ENOMEM);

	umem->context    = context;
	umem->length     = size;
	umem->address    = addr;
	umem->page_shift = PAGE_SHIFT;
	umem->writable   = 1;

	odp_data = kzalloc(sizeof(*odp_data), GFP_KERNEL);
	if (!odp_data) {
		ret = -ENOMEM;
		goto out_umem;
	}
	odp_data->umem = umem;

	mutex_init(&odp_data->umem_mutex);
	init_completion(&odp_data->notifier_completion);

	odp_data->page_list =
		vzalloc(array_size(pages, sizeof(*odp_data->page_list)));
	if (!odp_data->page_list) {
		ret = -ENOMEM;
		goto out_odp_data;
	}

	odp_data->dma_list =
		vzalloc(array_size(pages, sizeof(*odp_data->dma_list)));
	if (!odp_data->dma_list) {
		ret = -ENOMEM;
		goto out_page_list;
	}

	down_write(&context->umem_rwsem);
	context->odp_mrs_count++;
	rbt_ib_umem_insert(&odp_data->interval_tree, &context->umem_tree);
	if (likely(!atomic_read(&context->notifier_count)))
		odp_data->mn_counters_active = true;
	else
		list_add(&odp_data->no_private_counters,
			 &context->no_private_counters);
	up_write(&context->umem_rwsem);

	umem->odp_data = odp_data;

	return umem;

out_page_list:
	vfree(odp_data->page_list);
out_odp_data:
	kfree(odp_data);
out_umem:
	kfree(umem);
	return ERR_PTR(ret);
}