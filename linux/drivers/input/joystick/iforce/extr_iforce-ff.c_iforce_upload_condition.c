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
typedef  int u8 ;
struct resource {int /*<<< orphan*/  start; } ;
struct iforce_core_effect {int /*<<< orphan*/  flags; struct resource mod2_chunk; struct resource mod1_chunk; } ;
struct iforce {struct iforce_core_effect* core_effects; } ;
struct TYPE_8__ {int /*<<< orphan*/  interval; int /*<<< orphan*/  button; } ;
struct TYPE_7__ {int /*<<< orphan*/  delay; int /*<<< orphan*/  length; } ;
struct TYPE_6__ {TYPE_1__* condition; } ;
struct ff_effect {int id; int type; int /*<<< orphan*/  direction; TYPE_4__ trigger; TYPE_3__ replay; TYPE_2__ u; } ;
struct TYPE_5__ {int /*<<< orphan*/  center; int /*<<< orphan*/  deadband; int /*<<< orphan*/  left_coeff; int /*<<< orphan*/  right_coeff; int /*<<< orphan*/  left_saturation; int /*<<< orphan*/  right_saturation; } ;

/* Variables and functions */
#define  FF_DAMPER 129 
 int /*<<< orphan*/  FF_MOD1_IS_USED ; 
 int /*<<< orphan*/  FF_MOD2_IS_USED ; 
#define  FF_SPRING 128 
 int make_condition_modifier (struct iforce*,struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int make_core (struct iforce*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ need_condition_modifier (struct iforce*,struct ff_effect*,struct ff_effect*) ; 
 scalar_t__ need_core (struct ff_effect*,struct ff_effect*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int iforce_upload_condition(struct iforce *iforce, struct ff_effect *effect, struct ff_effect *old)
{
	int core_id = effect->id;
	struct iforce_core_effect* core_effect = iforce->core_effects + core_id;
	struct resource* mod1_chunk = &(core_effect->mod1_chunk);
	struct resource* mod2_chunk = &(core_effect->mod2_chunk);
	u8 type;
	int param_err = 1;
	int core_err = 0;

	switch (effect->type) {
	case FF_SPRING:	type = 0x40; break;
	case FF_DAMPER:	type = 0x41; break;
	default: return -1;
	}

	if (!old || need_condition_modifier(iforce, old, effect)) {
		param_err = make_condition_modifier(iforce, mod1_chunk,
			old != NULL,
			effect->u.condition[0].right_saturation,
			effect->u.condition[0].left_saturation,
			effect->u.condition[0].right_coeff,
			effect->u.condition[0].left_coeff,
			effect->u.condition[0].deadband,
			effect->u.condition[0].center);
		if (param_err)
			return param_err;
		set_bit(FF_MOD1_IS_USED, core_effect->flags);

		param_err = make_condition_modifier(iforce, mod2_chunk,
			old != NULL,
			effect->u.condition[1].right_saturation,
			effect->u.condition[1].left_saturation,
			effect->u.condition[1].right_coeff,
			effect->u.condition[1].left_coeff,
			effect->u.condition[1].deadband,
			effect->u.condition[1].center);
		if (param_err)
			return param_err;
		set_bit(FF_MOD2_IS_USED, core_effect->flags);

	}

	if (!old || need_core(old, effect)) {
		core_err = make_core(iforce, effect->id,
			mod1_chunk->start, mod2_chunk->start,
			type, 0xc0,
			effect->replay.length, effect->replay.delay,
			effect->trigger.button, effect->trigger.interval,
			effect->direction);
	}

	/* If the parameter creation failed, we already returned an
	 * error code.
	 * If the core creation failed, we return its error code.
	 * Else: if a parameter  was created, we return 0
	 *       else we return 1;
	 */
	return core_err < 0 ? core_err : param_err;
}