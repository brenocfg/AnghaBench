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
struct magicmouse_sc {int ntouches; int* tracking_ids; TYPE_1__* touches; } ;
struct TYPE_2__ {int size; } ;

/* Variables and functions */

__attribute__((used)) static int magicmouse_firm_touch(struct magicmouse_sc *msc)
{
	int touch = -1;
	int ii;

	/* If there is only one "firm" touch, set touch to its
	 * tracking ID.
	 */
	for (ii = 0; ii < msc->ntouches; ii++) {
		int idx = msc->tracking_ids[ii];
		if (msc->touches[idx].size < 8) {
			/* Ignore this touch. */
		} else if (touch >= 0) {
			touch = -1;
			break;
		} else {
			touch = idx;
		}
	}

	return touch;
}