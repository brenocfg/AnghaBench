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
typedef  int u8 ;
struct psmouse {int resolution; int /*<<< orphan*/  ps2dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSMOUSE_CMD_SETRES ; 
 int /*<<< orphan*/  ps2_command (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 

void psmouse_set_resolution(struct psmouse *psmouse, unsigned int resolution)
{
	static const u8 params[] = { 0, 1, 2, 2, 3 };
	u8 p;

	if (resolution == 0 || resolution > 200)
		resolution = 200;

	p = params[resolution / 50];
	ps2_command(&psmouse->ps2dev, &p, PSMOUSE_CMD_SETRES);
	psmouse->resolution = 25 << p;
}