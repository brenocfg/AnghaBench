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
struct ml_effect_state {unsigned long play_at; int /*<<< orphan*/  flags; } ;
struct ml_device {int /*<<< orphan*/  timer; struct ml_effect_state* states; } ;

/* Variables and functions */
 int /*<<< orphan*/  FF_EFFECT_PLAYING ; 
 int /*<<< orphan*/  FF_EFFECT_STARTED ; 
 int FF_MEMLESS_EFFECTS ; 
 unsigned long calculate_next_time (struct ml_effect_state*) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 scalar_t__ time_before_eq (unsigned long,unsigned long) ; 

__attribute__((used)) static void ml_schedule_timer(struct ml_device *ml)
{
	struct ml_effect_state *state;
	unsigned long now = jiffies;
	unsigned long earliest = 0;
	unsigned long next_at;
	int events = 0;
	int i;

	pr_debug("calculating next timer\n");

	for (i = 0; i < FF_MEMLESS_EFFECTS; i++) {

		state = &ml->states[i];

		if (!test_bit(FF_EFFECT_STARTED, &state->flags))
			continue;

		if (test_bit(FF_EFFECT_PLAYING, &state->flags))
			next_at = calculate_next_time(state);
		else
			next_at = state->play_at;

		if (time_before_eq(now, next_at) &&
		    (++events == 1 || time_before(next_at, earliest)))
			earliest = next_at;
	}

	if (!events) {
		pr_debug("no actions\n");
		del_timer(&ml->timer);
	} else {
		pr_debug("timer set\n");
		mod_timer(&ml->timer, earliest);
	}
}