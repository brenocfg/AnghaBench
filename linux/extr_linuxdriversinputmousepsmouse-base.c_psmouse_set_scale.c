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
struct psmouse {int /*<<< orphan*/  ps2dev; } ;
typedef  enum psmouse_scale { ____Placeholder_psmouse_scale } psmouse_scale ;

/* Variables and functions */
 int /*<<< orphan*/  PSMOUSE_CMD_SETSCALE11 ; 
 int /*<<< orphan*/  PSMOUSE_CMD_SETSCALE21 ; 
 int PSMOUSE_SCALE21 ; 
 int /*<<< orphan*/  ps2_command (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void psmouse_set_scale(struct psmouse *psmouse, enum psmouse_scale scale)
{
	ps2_command(&psmouse->ps2dev, NULL,
		    scale == PSMOUSE_SCALE21 ? PSMOUSE_CMD_SETSCALE21 :
					       PSMOUSE_CMD_SETSCALE11);
}