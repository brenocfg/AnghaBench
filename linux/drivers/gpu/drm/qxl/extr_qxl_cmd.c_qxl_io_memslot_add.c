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
typedef  int /*<<< orphan*/  uint8_t ;
struct qxl_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QXL_IO_MEMSLOT_ADD_ASYNC ; 
 int /*<<< orphan*/  wait_for_io_cmd (struct qxl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void qxl_io_memslot_add(struct qxl_device *qdev, uint8_t id)
{
	DRM_DEBUG_DRIVER("qxl_memslot_add %d\n", id);
	wait_for_io_cmd(qdev, id, QXL_IO_MEMSLOT_ADD_ASYNC);
}