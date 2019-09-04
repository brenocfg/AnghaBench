#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ml_effect_state {struct ff_effect* effect; } ;
struct TYPE_9__ {void* weak_magnitude; void* strong_magnitude; } ;
struct TYPE_8__ {int /*<<< orphan*/  envelope; int /*<<< orphan*/  magnitude; } ;
struct TYPE_7__ {void* end_level; void* start_level; } ;
struct TYPE_6__ {int /*<<< orphan*/  envelope; int /*<<< orphan*/  level; } ;
struct TYPE_10__ {TYPE_4__ rumble; TYPE_3__ periodic; TYPE_2__ ramp; TYPE_1__ constant; } ;
struct ff_effect {int type; int direction; TYPE_5__ u; } ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
#define  FF_CONSTANT 130 
#define  FF_PERIODIC 129 
#define  FF_RUMBLE 128 
 int /*<<< orphan*/  abs (int /*<<< orphan*/ ) ; 
 unsigned int apply_envelope (struct ml_effect_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* clamp_val (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  fixp_cos16 (unsigned int) ; 
 int fixp_mult (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixp_new16 (unsigned int) ; 
 int /*<<< orphan*/  fixp_sin16 (unsigned int) ; 
 void* min (int /*<<< orphan*/ ,int) ; 
 void* ml_calculate_direction (int,void*,int,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void ml_combine_effects(struct ff_effect *effect,
			       struct ml_effect_state *state,
			       int gain)
{
	struct ff_effect *new = state->effect;
	unsigned int strong, weak, i;
	int x, y;
	s16 level;

	switch (new->type) {
	case FF_CONSTANT:
		i = new->direction * 360 / 0xffff;
		level = fixp_new16(apply_envelope(state,
					new->u.constant.level,
					&new->u.constant.envelope));
		x = fixp_mult(fixp_sin16(i), level) * gain / 0xffff;
		y = fixp_mult(-fixp_cos16(i), level) * gain / 0xffff;
		/*
		 * here we abuse ff_ramp to hold x and y of constant force
		 * If in future any driver wants something else than x and y
		 * in s8, this should be changed to something more generic
		 */
		effect->u.ramp.start_level =
			clamp_val(effect->u.ramp.start_level + x, -0x80, 0x7f);
		effect->u.ramp.end_level =
			clamp_val(effect->u.ramp.end_level + y, -0x80, 0x7f);
		break;

	case FF_RUMBLE:
		strong = (u32)new->u.rumble.strong_magnitude * gain / 0xffff;
		weak = (u32)new->u.rumble.weak_magnitude * gain / 0xffff;

		if (effect->u.rumble.strong_magnitude + strong)
			effect->direction = ml_calculate_direction(
				effect->direction,
				effect->u.rumble.strong_magnitude,
				new->direction, strong);
		else if (effect->u.rumble.weak_magnitude + weak)
			effect->direction = ml_calculate_direction(
				effect->direction,
				effect->u.rumble.weak_magnitude,
				new->direction, weak);
		else
			effect->direction = 0;
		effect->u.rumble.strong_magnitude =
			min(strong + effect->u.rumble.strong_magnitude,
			    0xffffU);
		effect->u.rumble.weak_magnitude =
			min(weak + effect->u.rumble.weak_magnitude, 0xffffU);
		break;

	case FF_PERIODIC:
		i = apply_envelope(state, abs(new->u.periodic.magnitude),
				   &new->u.periodic.envelope);

		/* here we also scale it 0x7fff => 0xffff */
		i = i * gain / 0x7fff;

		if (effect->u.rumble.strong_magnitude + i)
			effect->direction = ml_calculate_direction(
				effect->direction,
				effect->u.rumble.strong_magnitude,
				new->direction, i);
		else
			effect->direction = 0;
		effect->u.rumble.strong_magnitude =
			min(i + effect->u.rumble.strong_magnitude, 0xffffU);
		effect->u.rumble.weak_magnitude =
			min(i + effect->u.rumble.weak_magnitude, 0xffffU);
		break;

	default:
		pr_err("invalid type in ml_combine_effects()\n");
		break;
	}

}