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
 int /*<<< orphan*/  PSMOUSE_CMD_ENABLE ; 
 int /*<<< orphan*/  PSMOUSE_CMD_SETRATE ; 
 int /*<<< orphan*/  PSMOUSE_CMD_SETSTREAM ; 
 scalar_t__ alps_command_mode_write_reg (struct psmouse*,int,int) ; 
 scalar_t__ alps_enter_command_mode (struct psmouse*) ; 
 scalar_t__ alps_exit_command_mode (struct psmouse*) ; 
 int ps2_command (struct ps2dev*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alps_hw_init_ss4_v2(struct psmouse *psmouse)
{
	struct ps2dev *ps2dev = &psmouse->ps2dev;
	char param[2] = {0x64, 0x28};
	int ret = -1;

	/* enter absolute mode */
	if (ps2_command(ps2dev, NULL, PSMOUSE_CMD_SETSTREAM) ||
	    ps2_command(ps2dev, NULL, PSMOUSE_CMD_SETSTREAM) ||
	    ps2_command(ps2dev, &param[0], PSMOUSE_CMD_SETRATE) ||
	    ps2_command(ps2dev, &param[1], PSMOUSE_CMD_SETRATE)) {
		goto error;
	}

	/* T.B.D. Decread noise packet number, delete in the future */
	if (alps_exit_command_mode(psmouse) ||
	    alps_enter_command_mode(psmouse) ||
	    alps_command_mode_write_reg(psmouse, 0x001D, 0x20)) {
		goto error;
	}
	alps_exit_command_mode(psmouse);

	return ps2_command(ps2dev, NULL, PSMOUSE_CMD_ENABLE);

error:
	alps_exit_command_mode(psmouse);
	return ret;
}