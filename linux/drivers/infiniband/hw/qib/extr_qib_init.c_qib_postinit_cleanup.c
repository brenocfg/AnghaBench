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
struct qib_devdata {int /*<<< orphan*/  (* f_cleanup ) (struct qib_devdata*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_device_data (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_free_devdata (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_pcie_ddcleanup (struct qib_devdata*) ; 
 int /*<<< orphan*/  stub1 (struct qib_devdata*) ; 

__attribute__((used)) static void qib_postinit_cleanup(struct qib_devdata *dd)
{
	/*
	 * Clean up chip-specific stuff.
	 * We check for NULL here, because it's outside
	 * the kregbase check, and we need to call it
	 * after the free_irq.  Thus it's possible that
	 * the function pointers were never initialized.
	 */
	if (dd->f_cleanup)
		dd->f_cleanup(dd);

	qib_pcie_ddcleanup(dd);

	cleanup_device_data(dd);

	qib_free_devdata(dd);
}