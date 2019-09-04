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
struct ps2dev {int dummy; } ;
struct psmouse {struct elantech_data* private; struct ps2dev ps2dev; } ;
struct elantech_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETP_PS2_COMMAND_DELAY ; 
 int ETP_PS2_COMMAND_TRIES ; 
 int /*<<< orphan*/  elantech_debug (char*,int,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int ps2_command (struct ps2dev*,unsigned char*,int) ; 
 int /*<<< orphan*/  psmouse_err (struct psmouse*,char*,int) ; 

__attribute__((used)) static int elantech_ps2_command(struct psmouse *psmouse,
				unsigned char *param, int command)
{
	struct ps2dev *ps2dev = &psmouse->ps2dev;
	struct elantech_data *etd = psmouse->private;
	int rc;
	int tries = ETP_PS2_COMMAND_TRIES;

	do {
		rc = ps2_command(ps2dev, param, command);
		if (rc == 0)
			break;
		tries--;
		elantech_debug("retrying ps2 command 0x%02x (%d).\n",
				command, tries);
		msleep(ETP_PS2_COMMAND_DELAY);
	} while (tries > 0);

	if (rc)
		psmouse_err(psmouse, "ps2 command 0x%02x failed.\n", command);

	return rc;
}