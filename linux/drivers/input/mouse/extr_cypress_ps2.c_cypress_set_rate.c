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
struct psmouse {int rate; int /*<<< orphan*/  ps2dev; struct cytp_data* private; } ;
struct cytp_data {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CYTP_BIT_HIGH_RATE ; 
 int /*<<< orphan*/  PSMOUSE_CMD_SETRATE ; 
 int /*<<< orphan*/  ps2_command (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cypress_set_rate(struct psmouse *psmouse, unsigned int rate)
{
	struct cytp_data *cytp = psmouse->private;

	if (rate >= 80) {
		psmouse->rate = 80;
		cytp->mode |= CYTP_BIT_HIGH_RATE;
	} else {
		psmouse->rate = 40;
		cytp->mode &= ~CYTP_BIT_HIGH_RATE;
	}

	ps2_command(&psmouse->ps2dev, (unsigned char *)&psmouse->rate,
		    PSMOUSE_CMD_SETRATE);
}