#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pidff_device {int* type_id; int /*<<< orphan*/  hid; TYPE_4__* create_new_effect_type; TYPE_2__* set_effect_type; } ;
struct input_dev {int /*<<< orphan*/  ffbit; } ;
typedef  int /*<<< orphan*/  pidff_effect_types ;
struct TYPE_8__ {TYPE_3__* usage; } ;
struct TYPE_7__ {scalar_t__ hid; } ;
struct TYPE_6__ {TYPE_1__* usage; } ;
struct TYPE_5__ {scalar_t__ hid; } ;

/* Variables and functions */
 int /*<<< orphan*/  FF_CONSTANT ; 
 int /*<<< orphan*/  FF_DAMPER ; 
 int /*<<< orphan*/  FF_FRICTION ; 
 int /*<<< orphan*/  FF_INERTIA ; 
 int /*<<< orphan*/  FF_PERIODIC ; 
 int /*<<< orphan*/  FF_RAMP ; 
 int /*<<< orphan*/  FF_SAW_DOWN ; 
 int /*<<< orphan*/  FF_SAW_UP ; 
 int /*<<< orphan*/  FF_SINE ; 
 int /*<<< orphan*/  FF_SPRING ; 
 int /*<<< orphan*/  FF_SQUARE ; 
 int /*<<< orphan*/  FF_TRIANGLE ; 
 size_t PID_CONSTANT ; 
 size_t PID_DAMPER ; 
 size_t PID_FRICTION ; 
 size_t PID_INERTIA ; 
 size_t PID_RAMP ; 
 size_t PID_SAW_DOWN ; 
 size_t PID_SAW_UP ; 
 size_t PID_SINE ; 
 size_t PID_SPRING ; 
 size_t PID_SQUARE ; 
 size_t PID_TRIANGLE ; 
 int /*<<< orphan*/  hid_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pidff_find_effects(struct pidff_device *pidff,
			      struct input_dev *dev)
{
	int i;

	for (i = 0; i < sizeof(pidff_effect_types); i++) {
		int pidff_type = pidff->type_id[i];
		if (pidff->set_effect_type->usage[pidff_type].hid !=
		    pidff->create_new_effect_type->usage[pidff_type].hid) {
			hid_err(pidff->hid,
				"effect type number %d is invalid\n", i);
			return -1;
		}
	}

	if (pidff->type_id[PID_CONSTANT])
		set_bit(FF_CONSTANT, dev->ffbit);
	if (pidff->type_id[PID_RAMP])
		set_bit(FF_RAMP, dev->ffbit);
	if (pidff->type_id[PID_SQUARE]) {
		set_bit(FF_SQUARE, dev->ffbit);
		set_bit(FF_PERIODIC, dev->ffbit);
	}
	if (pidff->type_id[PID_SINE]) {
		set_bit(FF_SINE, dev->ffbit);
		set_bit(FF_PERIODIC, dev->ffbit);
	}
	if (pidff->type_id[PID_TRIANGLE]) {
		set_bit(FF_TRIANGLE, dev->ffbit);
		set_bit(FF_PERIODIC, dev->ffbit);
	}
	if (pidff->type_id[PID_SAW_UP]) {
		set_bit(FF_SAW_UP, dev->ffbit);
		set_bit(FF_PERIODIC, dev->ffbit);
	}
	if (pidff->type_id[PID_SAW_DOWN]) {
		set_bit(FF_SAW_DOWN, dev->ffbit);
		set_bit(FF_PERIODIC, dev->ffbit);
	}
	if (pidff->type_id[PID_SPRING])
		set_bit(FF_SPRING, dev->ffbit);
	if (pidff->type_id[PID_DAMPER])
		set_bit(FF_DAMPER, dev->ffbit);
	if (pidff->type_id[PID_INERTIA])
		set_bit(FF_INERTIA, dev->ffbit);
	if (pidff->type_id[PID_FRICTION])
		set_bit(FF_FRICTION, dev->ffbit);

	return 0;

}