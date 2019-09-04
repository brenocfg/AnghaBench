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
 unsigned char fsp_test_invert_cmd (int) ; 
 unsigned char fsp_test_swap_cmd (int) ; 
 int /*<<< orphan*/  ps2_begin_command (struct ps2dev*) ; 
 int /*<<< orphan*/  ps2_end_command (struct ps2dev*) ; 
 scalar_t__ ps2_sendbyte (struct ps2dev*,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psmouse_dbg (struct psmouse*,char*,int,int) ; 

__attribute__((used)) static int fsp_page_reg_write(struct psmouse *psmouse, int reg_val)
{
	struct ps2dev *ps2dev = &psmouse->ps2dev;
	unsigned char v;
	int rc = -1;

	ps2_begin_command(ps2dev);

	if (ps2_sendbyte(ps2dev, 0xf3, FSP_CMD_TIMEOUT) < 0)
		goto out;

	ps2_sendbyte(ps2dev, 0x38, FSP_CMD_TIMEOUT2);
	ps2_sendbyte(ps2dev, 0x88, FSP_CMD_TIMEOUT2);

	if (ps2_sendbyte(ps2dev, 0xf3, FSP_CMD_TIMEOUT) < 0)
		goto out;

	if ((v = fsp_test_invert_cmd(reg_val)) != reg_val) {
		ps2_sendbyte(ps2dev, 0x47, FSP_CMD_TIMEOUT2);
	} else if ((v = fsp_test_swap_cmd(reg_val)) != reg_val) {
		/* swapping is required */
		ps2_sendbyte(ps2dev, 0x44, FSP_CMD_TIMEOUT2);
	} else {
		/* swapping isn't necessary */
		ps2_sendbyte(ps2dev, 0x33, FSP_CMD_TIMEOUT2);
	}

	ps2_sendbyte(ps2dev, v, FSP_CMD_TIMEOUT2);
	rc = 0;

 out:
	ps2_end_command(ps2dev);
	psmouse_dbg(psmouse,
		    "WRITE PAGE REG: to 0x%02x (rc = %d)\n",
		    reg_val, rc);
	return rc;
}