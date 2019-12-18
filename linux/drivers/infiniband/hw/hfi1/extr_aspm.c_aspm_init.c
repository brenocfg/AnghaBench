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
typedef  scalar_t__ u16 ;
struct hfi1_devdata {scalar_t__ first_dyn_alloc_ctxt; int aspm_enabled; int /*<<< orphan*/  aspm_supported; int /*<<< orphan*/  aspm_lock; } ;
struct hfi1_ctxtdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  aspm_ctx_init (struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  aspm_enable_all (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  aspm_hw_disable_l1 (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  aspm_hw_l1_supported (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  aspm_hw_set_l1_ent_latency (struct hfi1_devdata*) ; 
 struct hfi1_ctxtdata* hfi1_rcd_get_by_index (struct hfi1_devdata*,scalar_t__) ; 
 int /*<<< orphan*/  hfi1_rcd_put (struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void aspm_init(struct hfi1_devdata *dd)
{
	struct hfi1_ctxtdata *rcd;
	u16 i;

	spin_lock_init(&dd->aspm_lock);
	dd->aspm_supported = aspm_hw_l1_supported(dd);

	for (i = 0; i < dd->first_dyn_alloc_ctxt; i++) {
		rcd = hfi1_rcd_get_by_index(dd, i);
		if (rcd)
			aspm_ctx_init(rcd);
		hfi1_rcd_put(rcd);
	}

	/* Start with ASPM disabled */
	aspm_hw_set_l1_ent_latency(dd);
	dd->aspm_enabled = false;
	aspm_hw_disable_l1(dd);

	/* Now turn on ASPM if configured */
	aspm_enable_all(dd);
}