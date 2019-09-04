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
struct qxl_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  qxl_bo_force_delete (struct qxl_device*) ; 

void qxl_gem_fini(struct qxl_device *qdev)
{
	qxl_bo_force_delete(qdev);
}