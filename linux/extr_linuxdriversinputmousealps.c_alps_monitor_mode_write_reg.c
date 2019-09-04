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
typedef  int u16 ;
struct ps2dev {int dummy; } ;
struct psmouse {struct ps2dev ps2dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSMOUSE_CMD_DISABLE ; 
 int /*<<< orphan*/  PSMOUSE_CMD_ENABLE ; 
 scalar_t__ alps_monitor_mode_send_word (struct psmouse*,int) ; 
 scalar_t__ ps2_command (struct ps2dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alps_monitor_mode_write_reg(struct psmouse *psmouse,
				       u16 addr, u16 value)
{
	struct ps2dev *ps2dev = &psmouse->ps2dev;

	/* 0x0A0 is the command to write the word */
	if (ps2_command(ps2dev, NULL, PSMOUSE_CMD_ENABLE) ||
	    alps_monitor_mode_send_word(psmouse, 0x0A0) ||
	    alps_monitor_mode_send_word(psmouse, addr) ||
	    alps_monitor_mode_send_word(psmouse, value) ||
	    ps2_command(ps2dev, NULL, PSMOUSE_CMD_DISABLE))
		return -1;

	return 0;
}