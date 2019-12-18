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
struct tid_group {int size; int base; } ;
struct TYPE_2__ {int group_size; } ;
struct hfi1_devdata {TYPE_1__ rcv_entries; } ;
struct hfi1_ctxtdata {int expected_count; int expected_base; int /*<<< orphan*/  tid_group_list; struct tid_group* groups; int /*<<< orphan*/  numa_id; struct hfi1_devdata* dd; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct tid_group* kcalloc_node (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tid_group_add_tail (struct tid_group*,int /*<<< orphan*/ *) ; 

int hfi1_alloc_ctxt_rcv_groups(struct hfi1_ctxtdata *rcd)
{
	struct hfi1_devdata *dd = rcd->dd;
	u32 tidbase;
	struct tid_group *grp;
	int i;
	u32 ngroups;

	ngroups = rcd->expected_count / dd->rcv_entries.group_size;
	rcd->groups =
		kcalloc_node(ngroups, sizeof(*rcd->groups),
			     GFP_KERNEL, rcd->numa_id);
	if (!rcd->groups)
		return -ENOMEM;
	tidbase = rcd->expected_base;
	for (i = 0; i < ngroups; i++) {
		grp = &rcd->groups[i];
		grp->size = dd->rcv_entries.group_size;
		grp->base = tidbase;
		tid_group_add_tail(grp, &rcd->tid_group_list);
		tidbase += dd->rcv_entries.group_size;
	}

	return 0;
}