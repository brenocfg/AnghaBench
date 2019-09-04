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
struct hfi1_devdata {int /*<<< orphan*/ * piobase; int /*<<< orphan*/ * rcvarray_wc; int /*<<< orphan*/ * kregbase2; int /*<<< orphan*/ * kregbase1; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI1_PRESENT ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 

void hfi1_pcie_ddcleanup(struct hfi1_devdata *dd)
{
	dd->flags &= ~HFI1_PRESENT;
	if (dd->kregbase1)
		iounmap(dd->kregbase1);
	dd->kregbase1 = NULL;
	if (dd->kregbase2)
		iounmap(dd->kregbase2);
	dd->kregbase2 = NULL;
	if (dd->rcvarray_wc)
		iounmap(dd->rcvarray_wc);
	dd->rcvarray_wc = NULL;
	if (dd->piobase)
		iounmap(dd->piobase);
	dd->piobase = NULL;
}