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
struct pidff_device {int /*<<< orphan*/  hid; TYPE_1__* block_load; } ;
struct input_dev {int /*<<< orphan*/  ffbit; } ;
struct TYPE_2__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  FF_CONSTANT ; 
 int /*<<< orphan*/  FF_DAMPER ; 
 int /*<<< orphan*/  FF_FRICTION ; 
 int /*<<< orphan*/  FF_GAIN ; 
 int /*<<< orphan*/  FF_INERTIA ; 
 int /*<<< orphan*/  FF_PERIODIC ; 
 int /*<<< orphan*/  FF_RAMP ; 
 int /*<<< orphan*/  FF_SPRING ; 
 scalar_t__ PIDFF_FIND_FIELDS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PID_BLOCK_FREE ; 
 int /*<<< orphan*/  PID_BLOCK_LOAD ; 
 int /*<<< orphan*/  PID_DEVICE_GAIN ; 
 size_t PID_EFFECT_BLOCK_INDEX ; 
 int /*<<< orphan*/  PID_EFFECT_OPERATION ; 
 int /*<<< orphan*/  PID_POOL ; 
 int /*<<< orphan*/  PID_SET_CONDITION ; 
 int /*<<< orphan*/  PID_SET_CONSTANT ; 
 int /*<<< orphan*/  PID_SET_EFFECT ; 
 int /*<<< orphan*/  PID_SET_ENVELOPE ; 
 int /*<<< orphan*/  PID_SET_PERIODIC ; 
 int /*<<< orphan*/  PID_SET_RAMP ; 
 int /*<<< orphan*/  block_free ; 
 int /*<<< orphan*/  block_load ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_gain ; 
 int /*<<< orphan*/  effect_operation ; 
 int /*<<< orphan*/  hid_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hid_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pidff_find_effects (struct pidff_device*,struct input_dev*) ; 
 scalar_t__ pidff_find_special_fields (struct pidff_device*) ; 
 int /*<<< orphan*/  pool ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_condition ; 
 int /*<<< orphan*/  set_constant ; 
 int /*<<< orphan*/  set_effect ; 
 int /*<<< orphan*/  set_envelope ; 
 int /*<<< orphan*/  set_periodic ; 
 int /*<<< orphan*/  set_ramp ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pidff_init_fields(struct pidff_device *pidff, struct input_dev *dev)
{
	int envelope_ok = 0;

	if (PIDFF_FIND_FIELDS(set_effect, PID_SET_EFFECT, 1)) {
		hid_err(pidff->hid, "unknown set_effect report layout\n");
		return -ENODEV;
	}

	PIDFF_FIND_FIELDS(block_load, PID_BLOCK_LOAD, 0);
	if (!pidff->block_load[PID_EFFECT_BLOCK_INDEX].value) {
		hid_err(pidff->hid, "unknown pid_block_load report layout\n");
		return -ENODEV;
	}

	if (PIDFF_FIND_FIELDS(effect_operation, PID_EFFECT_OPERATION, 1)) {
		hid_err(pidff->hid, "unknown effect_operation report layout\n");
		return -ENODEV;
	}

	if (PIDFF_FIND_FIELDS(block_free, PID_BLOCK_FREE, 1)) {
		hid_err(pidff->hid, "unknown pid_block_free report layout\n");
		return -ENODEV;
	}

	if (!PIDFF_FIND_FIELDS(set_envelope, PID_SET_ENVELOPE, 1))
		envelope_ok = 1;

	if (pidff_find_special_fields(pidff) || pidff_find_effects(pidff, dev))
		return -ENODEV;

	if (!envelope_ok) {
		if (test_and_clear_bit(FF_CONSTANT, dev->ffbit))
			hid_warn(pidff->hid,
				 "has constant effect but no envelope\n");
		if (test_and_clear_bit(FF_RAMP, dev->ffbit))
			hid_warn(pidff->hid,
				 "has ramp effect but no envelope\n");

		if (test_and_clear_bit(FF_PERIODIC, dev->ffbit))
			hid_warn(pidff->hid,
				 "has periodic effect but no envelope\n");
	}

	if (test_bit(FF_CONSTANT, dev->ffbit) &&
	    PIDFF_FIND_FIELDS(set_constant, PID_SET_CONSTANT, 1)) {
		hid_warn(pidff->hid, "unknown constant effect layout\n");
		clear_bit(FF_CONSTANT, dev->ffbit);
	}

	if (test_bit(FF_RAMP, dev->ffbit) &&
	    PIDFF_FIND_FIELDS(set_ramp, PID_SET_RAMP, 1)) {
		hid_warn(pidff->hid, "unknown ramp effect layout\n");
		clear_bit(FF_RAMP, dev->ffbit);
	}

	if ((test_bit(FF_SPRING, dev->ffbit) ||
	     test_bit(FF_DAMPER, dev->ffbit) ||
	     test_bit(FF_FRICTION, dev->ffbit) ||
	     test_bit(FF_INERTIA, dev->ffbit)) &&
	    PIDFF_FIND_FIELDS(set_condition, PID_SET_CONDITION, 1)) {
		hid_warn(pidff->hid, "unknown condition effect layout\n");
		clear_bit(FF_SPRING, dev->ffbit);
		clear_bit(FF_DAMPER, dev->ffbit);
		clear_bit(FF_FRICTION, dev->ffbit);
		clear_bit(FF_INERTIA, dev->ffbit);
	}

	if (test_bit(FF_PERIODIC, dev->ffbit) &&
	    PIDFF_FIND_FIELDS(set_periodic, PID_SET_PERIODIC, 1)) {
		hid_warn(pidff->hid, "unknown periodic effect layout\n");
		clear_bit(FF_PERIODIC, dev->ffbit);
	}

	PIDFF_FIND_FIELDS(pool, PID_POOL, 0);

	if (!PIDFF_FIND_FIELDS(device_gain, PID_DEVICE_GAIN, 1))
		set_bit(FF_GAIN, dev->ffbit);

	return 0;
}