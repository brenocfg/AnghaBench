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
struct TYPE_2__ {int /*<<< orphan*/  serio; } ;
struct psmouse {TYPE_1__ ps2dev; } ;
typedef  enum psmouse_state { ____Placeholder_psmouse_state } psmouse_state ;

/* Variables and functions */
 int /*<<< orphan*/  __psmouse_set_state (struct psmouse*,int) ; 
 int /*<<< orphan*/  serio_continue_rx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serio_pause_rx (int /*<<< orphan*/ ) ; 

void psmouse_set_state(struct psmouse *psmouse, enum psmouse_state new_state)
{
	serio_pause_rx(psmouse->ps2dev.serio);
	__psmouse_set_state(psmouse, new_state);
	serio_continue_rx(psmouse->ps2dev.serio);
}