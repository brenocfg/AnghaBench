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
typedef  int /*<<< orphan*/  PIA ;

/* Variables and functions */
 scalar_t__ pi_schedule_claimed (int /*<<< orphan*/ *,void (*) ()) ; 

void pi_do_claimed(PIA * pi, void (*cont) (void))
{
	if (pi_schedule_claimed(pi, cont))
		cont();
}