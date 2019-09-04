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
struct qxl_device {scalar_t__ io_base; } ;

/* Variables and functions */
 scalar_t__ QXL_IO_NOTIFY_OOM ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

void qxl_io_notify_oom(struct qxl_device *qdev)
{
	outb(0, qdev->io_base + QXL_IO_NOTIFY_OOM);
}