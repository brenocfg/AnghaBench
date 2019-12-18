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
 int /*<<< orphan*/  QXL_IO_FLUSH_SURFACES_ASYNC ; 
 int /*<<< orphan*/  wait_for_io_cmd (struct qxl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void qxl_io_flush_surfaces(struct qxl_device *qdev)
{
	wait_for_io_cmd(qdev, 0, QXL_IO_FLUSH_SURFACES_ASYNC);
}