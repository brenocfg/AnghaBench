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
struct psmouse {struct ps2dev ps2dev; } ;

/* Variables and functions */
 int CYTP_PS2_CMD_TRIES ; 
 int CYTP_PS2_ERROR ; 
 int CYTP_PS2_RETRY ; 
 int cypress_ps2_sendbyte (struct psmouse*,unsigned char) ; 
 int /*<<< orphan*/  ps2_begin_command (struct ps2dev*) ; 
 int /*<<< orphan*/  ps2_end_command (struct ps2dev*) ; 

__attribute__((used)) static int cypress_ps2_ext_cmd(struct psmouse *psmouse, unsigned short cmd,
			       unsigned char data)
{
	struct ps2dev *ps2dev = &psmouse->ps2dev;
	int tries = CYTP_PS2_CMD_TRIES;
	int rc;

	ps2_begin_command(ps2dev);

	do {
		/*
		 * Send extension command byte (0xE8 or 0xF3).
		 * If sending the command fails, send recovery command
		 * to make the device return to the ready state.
		 */
		rc = cypress_ps2_sendbyte(psmouse, cmd & 0xff);
		if (rc == CYTP_PS2_RETRY) {
			rc = cypress_ps2_sendbyte(psmouse, 0x00);
			if (rc == CYTP_PS2_RETRY)
				rc = cypress_ps2_sendbyte(psmouse, 0x0a);
		}
		if (rc == CYTP_PS2_ERROR)
			continue;

		rc = cypress_ps2_sendbyte(psmouse, data);
		if (rc == CYTP_PS2_RETRY)
			rc = cypress_ps2_sendbyte(psmouse, data);
		if (rc == CYTP_PS2_ERROR)
			continue;
		else
			break;
	} while (--tries > 0);

	ps2_end_command(ps2dev);

	return rc;
}