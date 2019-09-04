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
 int /*<<< orphan*/  FSP_CMD_TIMEOUT ; 
 int /*<<< orphan*/  FSP_CMD_TIMEOUT2 ; 
 int /*<<< orphan*/  PSMOUSE_CMD_GETINFO ; 
 scalar_t__ __ps2_command (struct ps2dev*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps2_begin_command (struct ps2dev*) ; 
 int /*<<< orphan*/  ps2_end_command (struct ps2dev*) ; 
 scalar_t__ ps2_sendbyte (struct ps2dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psmouse_activate (struct psmouse*) ; 
 int /*<<< orphan*/  psmouse_dbg (struct psmouse*,char*,int,int) ; 
 int /*<<< orphan*/  psmouse_deactivate (struct psmouse*) ; 

__attribute__((used)) static int fsp_page_reg_read(struct psmouse *psmouse, int *reg_val)
{
	struct ps2dev *ps2dev = &psmouse->ps2dev;
	unsigned char param[3];
	int rc = -1;

	psmouse_deactivate(psmouse);

	ps2_begin_command(ps2dev);

	if (ps2_sendbyte(ps2dev, 0xf3, FSP_CMD_TIMEOUT) < 0)
		goto out;

	ps2_sendbyte(ps2dev, 0x66, FSP_CMD_TIMEOUT2);
	ps2_sendbyte(ps2dev, 0x88, FSP_CMD_TIMEOUT2);

	if (ps2_sendbyte(ps2dev, 0xf3, FSP_CMD_TIMEOUT) < 0)
		goto out;

	ps2_sendbyte(ps2dev, 0x83, FSP_CMD_TIMEOUT2);
	ps2_sendbyte(ps2dev, 0x88, FSP_CMD_TIMEOUT2);

	/* get the returned result */
	if (__ps2_command(ps2dev, param, PSMOUSE_CMD_GETINFO))
		goto out;

	*reg_val = param[2];
	rc = 0;

 out:
	ps2_end_command(ps2dev);
	psmouse_activate(psmouse);
	psmouse_dbg(psmouse,
		    "READ PAGE REG: 0x%02x (rc = %d)\n",
		    *reg_val, rc);
	return rc;
}