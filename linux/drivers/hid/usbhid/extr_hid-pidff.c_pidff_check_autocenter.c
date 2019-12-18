#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pidff_device {TYPE_2__* block_load; int /*<<< orphan*/  hid; } ;
struct input_dev {int /*<<< orphan*/  ffbit; } ;
struct TYPE_4__ {scalar_t__* value; TYPE_1__* field; } ;
struct TYPE_3__ {scalar_t__ logical_minimum; } ;

/* Variables and functions */
 int /*<<< orphan*/  FF_AUTOCENTER ; 
 size_t PID_EFFECT_BLOCK_INDEX ; 
 int /*<<< orphan*/  hid_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hid_notice (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pidff_autocenter (struct pidff_device*,int) ; 
 int /*<<< orphan*/  pidff_erase_pid (struct pidff_device*,scalar_t__) ; 
 int pidff_request_effect_upload (struct pidff_device*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pidff_check_autocenter(struct pidff_device *pidff,
				  struct input_dev *dev)
{
	int error;

	/*
	 * Let's find out if autocenter modification is supported
	 * Specification doesn't specify anything, so we request an
	 * effect upload and cancel it immediately. If the approved
	 * effect id was one above the minimum, then we assume the first
	 * effect id is a built-in spring type effect used for autocenter
	 */

	error = pidff_request_effect_upload(pidff, 1);
	if (error) {
		hid_err(pidff->hid, "upload request failed\n");
		return error;
	}

	if (pidff->block_load[PID_EFFECT_BLOCK_INDEX].value[0] ==
	    pidff->block_load[PID_EFFECT_BLOCK_INDEX].field->logical_minimum + 1) {
		pidff_autocenter(pidff, 0xffff);
		set_bit(FF_AUTOCENTER, dev->ffbit);
	} else {
		hid_notice(pidff->hid,
			   "device has unknown autocenter control method\n");
	}

	pidff_erase_pid(pidff,
			pidff->block_load[PID_EFFECT_BLOCK_INDEX].value[0]);

	return 0;

}