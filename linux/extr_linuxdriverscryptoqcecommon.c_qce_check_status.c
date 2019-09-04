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
typedef  int u32 ;
struct qce_device {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int /*<<< orphan*/  OPERATION_DONE_SHIFT ; 
 int /*<<< orphan*/  REG_STATUS ; 
 int STATUS_ERRORS ; 
 int qce_read (struct qce_device*,int /*<<< orphan*/ ) ; 

int qce_check_status(struct qce_device *qce, u32 *status)
{
	int ret = 0;

	*status = qce_read(qce, REG_STATUS);

	/*
	 * Don't use result dump status. The operation may not be complete.
	 * Instead, use the status we just read from device. In case, we need to
	 * use result_status from result dump the result_status needs to be byte
	 * swapped, since we set the device to little endian.
	 */
	if (*status & STATUS_ERRORS || !(*status & BIT(OPERATION_DONE_SHIFT)))
		ret = -ENXIO;

	return ret;
}