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
struct scif_dev {int /*<<< orphan*/ * intr_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 

void scif_destroy_intr_wq(struct scif_dev *scifdev)
{
	if (scifdev->intr_wq) {
		destroy_workqueue(scifdev->intr_wq);
		scifdev->intr_wq = NULL;
	}
}