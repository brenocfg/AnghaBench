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
struct psmouse {int dummy; } ;

/* Variables and functions */
 int CYTP_PS2_CMD_TRIES ; 
 int /*<<< orphan*/  DECODE_CMD_AA (unsigned char) ; 
 int /*<<< orphan*/  DECODE_CMD_BB (unsigned char) ; 
 int /*<<< orphan*/  DECODE_CMD_CC (unsigned char) ; 
 int /*<<< orphan*/  DECODE_CMD_DD (unsigned char) ; 
 int EIO ; 
 int /*<<< orphan*/  PSMOUSE_CMD_SETRES ; 
 int /*<<< orphan*/  cypress_ps2_ext_cmd (struct psmouse*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cypress_ps2_read_cmd_status (struct psmouse*,unsigned char,unsigned char*) ; 
 scalar_t__ cypress_verify_cmd_state (struct psmouse*,unsigned char,unsigned char*) ; 
 int /*<<< orphan*/  psmouse_dbg (struct psmouse*,char*,unsigned char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cypress_send_ext_cmd(struct psmouse *psmouse, unsigned char cmd,
				unsigned char *param)
{
	int tries = CYTP_PS2_CMD_TRIES;
	int rc;

	psmouse_dbg(psmouse, "send extension cmd 0x%02x, [%d %d %d %d]\n",
		 cmd, DECODE_CMD_AA(cmd), DECODE_CMD_BB(cmd),
		 DECODE_CMD_CC(cmd), DECODE_CMD_DD(cmd));

	do {
		cypress_ps2_ext_cmd(psmouse,
				    PSMOUSE_CMD_SETRES, DECODE_CMD_DD(cmd));
		cypress_ps2_ext_cmd(psmouse,
				    PSMOUSE_CMD_SETRES, DECODE_CMD_CC(cmd));
		cypress_ps2_ext_cmd(psmouse,
				    PSMOUSE_CMD_SETRES, DECODE_CMD_BB(cmd));
		cypress_ps2_ext_cmd(psmouse,
				    PSMOUSE_CMD_SETRES, DECODE_CMD_AA(cmd));

		rc = cypress_ps2_read_cmd_status(psmouse, cmd, param);
		if (rc)
			continue;

		if (cypress_verify_cmd_state(psmouse, cmd, param))
			return 0;

	} while (--tries > 0);

	return -EIO;
}