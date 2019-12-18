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
struct scif_dev {int node; int /*<<< orphan*/  intr_bh; scalar_t__ intr_wq; int /*<<< orphan*/  intr_wqname; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ alloc_ordered_workqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_intr_bh_handler ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 

int scif_setup_intr_wq(struct scif_dev *scifdev)
{
	if (!scifdev->intr_wq) {
		snprintf(scifdev->intr_wqname, sizeof(scifdev->intr_wqname),
			 "SCIF INTR %d", scifdev->node);
		scifdev->intr_wq =
			alloc_ordered_workqueue(scifdev->intr_wqname, 0);
		if (!scifdev->intr_wq)
			return -ENOMEM;
		INIT_WORK(&scifdev->intr_bh, scif_intr_bh_handler);
	}
	return 0;
}