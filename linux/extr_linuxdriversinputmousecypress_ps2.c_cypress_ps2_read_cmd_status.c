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
struct ps2dev {int /*<<< orphan*/  wait; } ;
struct psmouse {int state; int pktcnt; int /*<<< orphan*/  packet; struct ps2dev ps2dev; } ;
typedef  enum psmouse_state { ____Placeholder_psmouse_state } psmouse_state ;

/* Variables and functions */
 unsigned char CYTP_CMD_READ_TP_METRICS ; 
 int /*<<< orphan*/  CYTP_CMD_TIMEOUT ; 
 int PSMOUSE_CMD_MODE ; 
 int cypress_ps2_sendbyte (struct psmouse*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps2_begin_command (struct ps2dev*) ; 
 int /*<<< orphan*/  ps2_end_command (struct ps2dev*) ; 
 int /*<<< orphan*/  psmouse_dbg (struct psmouse*,char*,unsigned char,int,unsigned char*) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cypress_ps2_read_cmd_status(struct psmouse *psmouse,
				       unsigned char cmd,
				       unsigned char *param)
{
	int rc;
	struct ps2dev *ps2dev = &psmouse->ps2dev;
	enum psmouse_state old_state;
	int pktsize;

	ps2_begin_command(ps2dev);

	old_state = psmouse->state;
	psmouse->state = PSMOUSE_CMD_MODE;
	psmouse->pktcnt = 0;

	pktsize = (cmd == CYTP_CMD_READ_TP_METRICS) ? 8 : 3;
	memset(param, 0, pktsize);

	rc = cypress_ps2_sendbyte(psmouse, 0xe9);
	if (rc < 0)
		goto out;

	wait_event_timeout(ps2dev->wait,
			(psmouse->pktcnt >= pktsize),
			msecs_to_jiffies(CYTP_CMD_TIMEOUT));

	memcpy(param, psmouse->packet, pktsize);

	psmouse_dbg(psmouse, "Command 0x%02x response data (0x): %*ph\n",
			cmd, pktsize, param);

out:
	psmouse->state = old_state;
	psmouse->pktcnt = 0;

	ps2_end_command(ps2dev);

	return rc;
}