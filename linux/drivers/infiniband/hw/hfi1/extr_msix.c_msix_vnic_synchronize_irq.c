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
struct hfi1_msix_entry {int /*<<< orphan*/  irq; } ;
struct TYPE_4__ {struct hfi1_msix_entry* msix_entries; } ;
struct TYPE_3__ {int num_ctxt; struct hfi1_ctxtdata** ctxt; } ;
struct hfi1_devdata {TYPE_2__ msix_info; TYPE_1__ vnic; } ;
struct hfi1_ctxtdata {size_t msix_intr; } ;

/* Variables and functions */
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

void msix_vnic_synchronize_irq(struct hfi1_devdata *dd)
{
	int i;

	for (i = 0; i < dd->vnic.num_ctxt; i++) {
		struct hfi1_ctxtdata *rcd = dd->vnic.ctxt[i];
		struct hfi1_msix_entry *me;

		me = &dd->msix_info.msix_entries[rcd->msix_intr];

		synchronize_irq(me->irq);
	}
}