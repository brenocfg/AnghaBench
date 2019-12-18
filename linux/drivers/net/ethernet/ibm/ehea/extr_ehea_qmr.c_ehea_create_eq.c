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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ehea_eqe {int dummy; } ;
struct TYPE_2__ {int type; int nr_pages; int /*<<< orphan*/  eqe_gen; int /*<<< orphan*/  max_nr_of_eqes; } ;
struct ehea_eq {int /*<<< orphan*/  fw_handle; int /*<<< orphan*/  hw_queue; TYPE_1__ attr; int /*<<< orphan*/  spinlock; struct ehea_adapter* adapter; } ;
struct ehea_adapter {int /*<<< orphan*/  handle; } ;
typedef  enum ehea_eq_type { ____Placeholder_ehea_eq_type } ehea_eq_type ;

/* Variables and functions */
 int /*<<< orphan*/  EHEA_EQ_REGISTER_ORIG ; 
 int /*<<< orphan*/  EHEA_PAGESIZE ; 
 int /*<<< orphan*/  FORCE_FREE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ H_PAGE_REGISTERED ; 
 scalar_t__ H_RESOURCE ; 
 scalar_t__ H_SUCCESS ; 
 scalar_t__ __pa (void*) ; 
 scalar_t__ ehea_h_alloc_resource_eq (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ehea_h_free_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ehea_h_register_rpage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  hw_qeit_reset (int /*<<< orphan*/ *) ; 
 void* hw_qpageit_get_inc (int /*<<< orphan*/ *) ; 
 int hw_queue_ctor (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hw_queue_dtor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ehea_eq*) ; 
 struct ehea_eq* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct ehea_eq *ehea_create_eq(struct ehea_adapter *adapter,
			       const enum ehea_eq_type type,
			       const u32 max_nr_of_eqes, const u8 eqe_gen)
{
	int ret, i;
	u64 hret, rpage;
	void *vpage;
	struct ehea_eq *eq;

	eq = kzalloc(sizeof(*eq), GFP_KERNEL);
	if (!eq)
		return NULL;

	eq->adapter = adapter;
	eq->attr.type = type;
	eq->attr.max_nr_of_eqes = max_nr_of_eqes;
	eq->attr.eqe_gen = eqe_gen;
	spin_lock_init(&eq->spinlock);

	hret = ehea_h_alloc_resource_eq(adapter->handle,
					&eq->attr, &eq->fw_handle);
	if (hret != H_SUCCESS) {
		pr_err("alloc_resource_eq failed\n");
		goto out_freemem;
	}

	ret = hw_queue_ctor(&eq->hw_queue, eq->attr.nr_pages,
			    EHEA_PAGESIZE, sizeof(struct ehea_eqe));
	if (ret) {
		pr_err("can't allocate eq pages\n");
		goto out_freeres;
	}

	for (i = 0; i < eq->attr.nr_pages; i++) {
		vpage = hw_qpageit_get_inc(&eq->hw_queue);
		if (!vpage) {
			pr_err("hw_qpageit_get_inc failed\n");
			hret = H_RESOURCE;
			goto out_kill_hwq;
		}

		rpage = __pa(vpage);

		hret = ehea_h_register_rpage(adapter->handle, 0,
					     EHEA_EQ_REGISTER_ORIG,
					     eq->fw_handle, rpage, 1);

		if (i == (eq->attr.nr_pages - 1)) {
			/* last page */
			vpage = hw_qpageit_get_inc(&eq->hw_queue);
			if ((hret != H_SUCCESS) || (vpage))
				goto out_kill_hwq;

		} else {
			if (hret != H_PAGE_REGISTERED)
				goto out_kill_hwq;

		}
	}

	hw_qeit_reset(&eq->hw_queue);
	return eq;

out_kill_hwq:
	hw_queue_dtor(&eq->hw_queue);

out_freeres:
	ehea_h_free_resource(adapter->handle, eq->fw_handle, FORCE_FREE);

out_freemem:
	kfree(eq);
	return NULL;
}