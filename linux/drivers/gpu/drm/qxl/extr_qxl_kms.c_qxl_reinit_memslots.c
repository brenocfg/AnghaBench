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
struct qxl_device {int /*<<< orphan*/  surfaces_slot; int /*<<< orphan*/  main_slot; } ;

/* Variables and functions */
 int /*<<< orphan*/  setup_hw_slot (struct qxl_device*,int /*<<< orphan*/ *) ; 

void qxl_reinit_memslots(struct qxl_device *qdev)
{
	setup_hw_slot(qdev, &qdev->main_slot);
	setup_hw_slot(qdev, &qdev->surfaces_slot);
}