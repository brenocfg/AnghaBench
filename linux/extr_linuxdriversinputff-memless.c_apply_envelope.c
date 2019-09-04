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
struct ml_effect_state {scalar_t__ stop_at; scalar_t__ play_at; struct ff_effect* effect; } ;
struct ff_envelope {int attack_length; int fade_length; int /*<<< orphan*/  fade_level; int /*<<< orphan*/  attack_level; } ;
struct TYPE_2__ {scalar_t__ length; } ;
struct ff_effect {TYPE_1__ replay; } ;

/* Variables and functions */
 int abs (int) ; 
 unsigned long jiffies ; 
 int jiffies_to_msecs (scalar_t__) ; 
 int min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 scalar_t__ time_after (unsigned long,scalar_t__) ; 
 scalar_t__ time_before (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  u16 ; 

__attribute__((used)) static int apply_envelope(struct ml_effect_state *state, int value,
			  struct ff_envelope *envelope)
{
	struct ff_effect *effect = state->effect;
	unsigned long now = jiffies;
	int time_from_level;
	int time_of_envelope;
	int envelope_level;
	int difference;

	if (envelope->attack_length &&
	    time_before(now,
			state->play_at + msecs_to_jiffies(envelope->attack_length))) {
		pr_debug("value = 0x%x, attack_level = 0x%x\n",
			 value, envelope->attack_level);
		time_from_level = jiffies_to_msecs(now - state->play_at);
		time_of_envelope = envelope->attack_length;
		envelope_level = min_t(u16, envelope->attack_level, 0x7fff);

	} else if (envelope->fade_length && effect->replay.length &&
		   time_after(now,
			      state->stop_at - msecs_to_jiffies(envelope->fade_length)) &&
		   time_before(now, state->stop_at)) {
		time_from_level = jiffies_to_msecs(state->stop_at - now);
		time_of_envelope = envelope->fade_length;
		envelope_level = min_t(u16, envelope->fade_level, 0x7fff);
	} else
		return value;

	difference = abs(value) - envelope_level;

	pr_debug("difference = %d\n", difference);
	pr_debug("time_from_level = 0x%x\n", time_from_level);
	pr_debug("time_of_envelope = 0x%x\n", time_of_envelope);

	difference = difference * time_from_level / time_of_envelope;

	pr_debug("difference = %d\n", difference);

	return value < 0 ?
		-(difference + envelope_level) : (difference + envelope_level);
}