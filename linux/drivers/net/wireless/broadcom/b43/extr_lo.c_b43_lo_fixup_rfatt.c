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
struct b43_rfatt {int att; int /*<<< orphan*/  with_padmix; } ;

/* Variables and functions */

__attribute__((used)) static inline void b43_lo_fixup_rfatt(struct b43_rfatt *rf)
{
	if (!rf->with_padmix)
		return;
	if ((rf->att != 1) && (rf->att != 2) && (rf->att != 3))
		rf->att = 4;
}