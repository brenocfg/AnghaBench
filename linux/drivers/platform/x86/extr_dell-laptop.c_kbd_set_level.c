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
typedef  scalar_t__ u8 ;
struct kbd_state {scalar_t__ level; scalar_t__ mode_bit; } ;
struct TYPE_2__ {scalar_t__ levels; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ KBD_MODE_BIT_OFF ; 
 TYPE_1__ kbd_info ; 
 scalar_t__* kbd_mode_levels ; 
 scalar_t__ kbd_mode_levels_count ; 
 scalar_t__ kbd_previous_level ; 
 scalar_t__ kbd_previous_mode_bit ; 

__attribute__((used)) static int kbd_set_level(struct kbd_state *state, u8 level)
{
	if (kbd_info.levels != 0) {
		if (level != 0)
			kbd_previous_level = level;
		if (state->level == level)
			return 0;
		state->level = level;
		if (level != 0 && state->mode_bit == KBD_MODE_BIT_OFF)
			state->mode_bit = kbd_previous_mode_bit;
		else if (level == 0 && state->mode_bit != KBD_MODE_BIT_OFF) {
			kbd_previous_mode_bit = state->mode_bit;
			state->mode_bit = KBD_MODE_BIT_OFF;
		}
		return 0;
	}

	if (kbd_mode_levels_count > 0 && level < kbd_mode_levels_count) {
		if (level != 0)
			kbd_previous_level = level;
		state->mode_bit = kbd_mode_levels[level];
		return 0;
	}

	return -EINVAL;
}