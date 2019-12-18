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
struct zynqmp_ipi_pdata {int num_mboxes; struct zynqmp_ipi_mbox* ipi_mboxes; } ;
struct TYPE_2__ {scalar_t__ parent; } ;
struct zynqmp_ipi_mbox {TYPE_1__ dev; int /*<<< orphan*/  mbox; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  mbox_controller_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zynqmp_ipi_free_mboxes(struct zynqmp_ipi_pdata *pdata)
{
	struct zynqmp_ipi_mbox *ipi_mbox;
	int i;

	i = pdata->num_mboxes;
	for (; i >= 0; i--) {
		ipi_mbox = &pdata->ipi_mboxes[i];
		if (ipi_mbox->dev.parent) {
			mbox_controller_unregister(&ipi_mbox->mbox);
			device_unregister(&ipi_mbox->dev);
		}
	}
}