#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * rc_qacks; void* rc_delayed_comp; int /*<<< orphan*/ * rc_acks; } ;
struct TYPE_4__ {TYPE_1__ rvp; } ;
struct hfi1_pportdata {TYPE_2__ ibport_data; } ;
struct hfi1_devdata {int num_pports; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* alloc_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64 ; 

__attribute__((used)) static inline int init_cpu_counters(struct hfi1_devdata *dd)
{
	struct hfi1_pportdata *ppd;
	int i;

	ppd = (struct hfi1_pportdata *)(dd + 1);
	for (i = 0; i < dd->num_pports; i++, ppd++) {
		ppd->ibport_data.rvp.rc_acks = NULL;
		ppd->ibport_data.rvp.rc_qacks = NULL;
		ppd->ibport_data.rvp.rc_acks = alloc_percpu(u64);
		ppd->ibport_data.rvp.rc_qacks = alloc_percpu(u64);
		ppd->ibport_data.rvp.rc_delayed_comp = alloc_percpu(u64);
		if (!ppd->ibport_data.rvp.rc_acks ||
		    !ppd->ibport_data.rvp.rc_delayed_comp ||
		    !ppd->ibport_data.rvp.rc_qacks)
			return -ENOMEM;
	}

	return 0;
}