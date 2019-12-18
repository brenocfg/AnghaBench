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
struct xen_pcibk_device {unsigned long flags; TYPE_1__* sh_info; int /*<<< orphan*/  op_work; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  _PCIB_op_pending ; 
 int /*<<< orphan*/  _PDEVF_op_active ; 
 int /*<<< orphan*/  _XEN_PCIB_active ; 
 int /*<<< orphan*/  _XEN_PCIF_active ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xen_pcibk_aer_wait_queue ; 

void xen_pcibk_test_and_schedule_op(struct xen_pcibk_device *pdev)
{
	/* Check that frontend is requesting an operation and that we are not
	 * already processing a request */
	if (test_bit(_XEN_PCIF_active, (unsigned long *)&pdev->sh_info->flags)
	    && !test_and_set_bit(_PDEVF_op_active, &pdev->flags)) {
		schedule_work(&pdev->op_work);
	}
	/*_XEN_PCIB_active should have been cleared by pcifront. And also make
	sure xen_pcibk is waiting for ack by checking _PCIB_op_pending*/
	if (!test_bit(_XEN_PCIB_active, (unsigned long *)&pdev->sh_info->flags)
	    && test_bit(_PCIB_op_pending, &pdev->flags)) {
		wake_up(&xen_pcibk_aer_wait_queue);
	}
}