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
typedef  int u16 ;
struct twl4030_keypad {int n_rows; } ;

/* Variables and functions */
 int hweight16 (int) ; 

__attribute__((used)) static bool twl4030_is_in_ghost_state(struct twl4030_keypad *kp, u16 *key_state)
{
	int i;
	u16 check = 0;

	for (i = 0; i < kp->n_rows; i++) {
		u16 col = key_state[i];

		if ((col & check) && hweight16(col) > 1)
			return true;

		check |= col;
	}

	return false;
}