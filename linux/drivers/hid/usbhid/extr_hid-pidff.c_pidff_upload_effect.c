#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pidff_device {int /*<<< orphan*/  hid; TYPE_6__* block_load; scalar_t__* pid_id; int /*<<< orphan*/ * type_id; } ;
struct input_dev {TYPE_1__* ff; } ;
struct TYPE_10__ {int /*<<< orphan*/  envelope; } ;
struct TYPE_9__ {int /*<<< orphan*/  envelope; int /*<<< orphan*/  waveform; } ;
struct TYPE_8__ {int /*<<< orphan*/  envelope; } ;
struct TYPE_11__ {TYPE_4__ ramp; TYPE_3__ periodic; TYPE_2__ constant; } ;
struct ff_effect {size_t id; int type; TYPE_5__ u; } ;
struct TYPE_12__ {scalar_t__* value; } ;
struct TYPE_7__ {struct pidff_device* private; } ;

/* Variables and functions */
 int EINVAL ; 
#define  FF_CONSTANT 139 
#define  FF_DAMPER 138 
#define  FF_FRICTION 137 
#define  FF_INERTIA 136 
#define  FF_PERIODIC 135 
#define  FF_RAMP 134 
#define  FF_SAW_DOWN 133 
#define  FF_SAW_UP 132 
#define  FF_SINE 131 
#define  FF_SPRING 130 
#define  FF_SQUARE 129 
#define  FF_TRIANGLE 128 
 size_t PID_CONSTANT ; 
 size_t PID_DAMPER ; 
 size_t PID_EFFECT_BLOCK_INDEX ; 
 size_t PID_FRICTION ; 
 size_t PID_INERTIA ; 
 size_t PID_RAMP ; 
 int PID_SAW_DOWN ; 
 int PID_SAW_UP ; 
 int PID_SINE ; 
 size_t PID_SPRING ; 
 int PID_SQUARE ; 
 int PID_TRIANGLE ; 
 int /*<<< orphan*/  hid_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hid_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pidff_needs_set_condition (struct ff_effect*,struct ff_effect*) ; 
 int /*<<< orphan*/  pidff_needs_set_constant (struct ff_effect*,struct ff_effect*) ; 
 int /*<<< orphan*/  pidff_needs_set_effect (struct ff_effect*,struct ff_effect*) ; 
 int /*<<< orphan*/  pidff_needs_set_envelope (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pidff_needs_set_periodic (struct ff_effect*,struct ff_effect*) ; 
 int /*<<< orphan*/  pidff_needs_set_ramp (struct ff_effect*,struct ff_effect*) ; 
 int pidff_request_effect_upload (struct pidff_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pidff_set_condition_report (struct pidff_device*,struct ff_effect*) ; 
 int /*<<< orphan*/  pidff_set_constant_force_report (struct pidff_device*,struct ff_effect*) ; 
 int /*<<< orphan*/  pidff_set_effect_report (struct pidff_device*,struct ff_effect*) ; 
 int /*<<< orphan*/  pidff_set_envelope_report (struct pidff_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pidff_set_periodic_report (struct pidff_device*,struct ff_effect*) ; 
 int /*<<< orphan*/  pidff_set_ramp_force_report (struct pidff_device*,struct ff_effect*) ; 

__attribute__((used)) static int pidff_upload_effect(struct input_dev *dev, struct ff_effect *effect,
			       struct ff_effect *old)
{
	struct pidff_device *pidff = dev->ff->private;
	int type_id;
	int error;

	pidff->block_load[PID_EFFECT_BLOCK_INDEX].value[0] = 0;
	if (old) {
		pidff->block_load[PID_EFFECT_BLOCK_INDEX].value[0] =
			pidff->pid_id[effect->id];
	}

	switch (effect->type) {
	case FF_CONSTANT:
		if (!old) {
			error = pidff_request_effect_upload(pidff,
					pidff->type_id[PID_CONSTANT]);
			if (error)
				return error;
		}
		if (!old || pidff_needs_set_effect(effect, old))
			pidff_set_effect_report(pidff, effect);
		if (!old || pidff_needs_set_constant(effect, old))
			pidff_set_constant_force_report(pidff, effect);
		if (!old ||
		    pidff_needs_set_envelope(&effect->u.constant.envelope,
					&old->u.constant.envelope))
			pidff_set_envelope_report(pidff,
					&effect->u.constant.envelope);
		break;

	case FF_PERIODIC:
		if (!old) {
			switch (effect->u.periodic.waveform) {
			case FF_SQUARE:
				type_id = PID_SQUARE;
				break;
			case FF_TRIANGLE:
				type_id = PID_TRIANGLE;
				break;
			case FF_SINE:
				type_id = PID_SINE;
				break;
			case FF_SAW_UP:
				type_id = PID_SAW_UP;
				break;
			case FF_SAW_DOWN:
				type_id = PID_SAW_DOWN;
				break;
			default:
				hid_err(pidff->hid, "invalid waveform\n");
				return -EINVAL;
			}

			error = pidff_request_effect_upload(pidff,
					pidff->type_id[type_id]);
			if (error)
				return error;
		}
		if (!old || pidff_needs_set_effect(effect, old))
			pidff_set_effect_report(pidff, effect);
		if (!old || pidff_needs_set_periodic(effect, old))
			pidff_set_periodic_report(pidff, effect);
		if (!old ||
		    pidff_needs_set_envelope(&effect->u.periodic.envelope,
					&old->u.periodic.envelope))
			pidff_set_envelope_report(pidff,
					&effect->u.periodic.envelope);
		break;

	case FF_RAMP:
		if (!old) {
			error = pidff_request_effect_upload(pidff,
					pidff->type_id[PID_RAMP]);
			if (error)
				return error;
		}
		if (!old || pidff_needs_set_effect(effect, old))
			pidff_set_effect_report(pidff, effect);
		if (!old || pidff_needs_set_ramp(effect, old))
			pidff_set_ramp_force_report(pidff, effect);
		if (!old ||
		    pidff_needs_set_envelope(&effect->u.ramp.envelope,
					&old->u.ramp.envelope))
			pidff_set_envelope_report(pidff,
					&effect->u.ramp.envelope);
		break;

	case FF_SPRING:
		if (!old) {
			error = pidff_request_effect_upload(pidff,
					pidff->type_id[PID_SPRING]);
			if (error)
				return error;
		}
		if (!old || pidff_needs_set_effect(effect, old))
			pidff_set_effect_report(pidff, effect);
		if (!old || pidff_needs_set_condition(effect, old))
			pidff_set_condition_report(pidff, effect);
		break;

	case FF_FRICTION:
		if (!old) {
			error = pidff_request_effect_upload(pidff,
					pidff->type_id[PID_FRICTION]);
			if (error)
				return error;
		}
		if (!old || pidff_needs_set_effect(effect, old))
			pidff_set_effect_report(pidff, effect);
		if (!old || pidff_needs_set_condition(effect, old))
			pidff_set_condition_report(pidff, effect);
		break;

	case FF_DAMPER:
		if (!old) {
			error = pidff_request_effect_upload(pidff,
					pidff->type_id[PID_DAMPER]);
			if (error)
				return error;
		}
		if (!old || pidff_needs_set_effect(effect, old))
			pidff_set_effect_report(pidff, effect);
		if (!old || pidff_needs_set_condition(effect, old))
			pidff_set_condition_report(pidff, effect);
		break;

	case FF_INERTIA:
		if (!old) {
			error = pidff_request_effect_upload(pidff,
					pidff->type_id[PID_INERTIA]);
			if (error)
				return error;
		}
		if (!old || pidff_needs_set_effect(effect, old))
			pidff_set_effect_report(pidff, effect);
		if (!old || pidff_needs_set_condition(effect, old))
			pidff_set_condition_report(pidff, effect);
		break;

	default:
		hid_err(pidff->hid, "invalid type\n");
		return -EINVAL;
	}

	if (!old)
		pidff->pid_id[effect->id] =
		    pidff->block_load[PID_EFFECT_BLOCK_INDEX].value[0];

	hid_dbg(pidff->hid, "uploaded\n");

	return 0;
}