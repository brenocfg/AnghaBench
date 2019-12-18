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
struct psmouse {struct ps2dev ps2dev; struct fsp_data* private; } ;
struct fsp_data {scalar_t__ ver; int buttons; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  FSPDRV_FLAG_EN_OPC ; 
 int FSP_BIT_EN_AUTO_MSID8 ; 
 int FSP_BIT_EN_MSID6 ; 
 int FSP_BIT_EN_MSID7 ; 
 int FSP_BIT_EN_MSID8 ; 
 int FSP_BIT_EN_PKT_G0 ; 
 int FSP_BIT_SWC1_EN_ABS_1F ; 
 int FSP_BIT_SWC1_EN_ABS_2F ; 
 int FSP_BIT_SWC1_EN_ABS_CON ; 
 int FSP_BIT_SWC1_EN_FUP_OUT ; 
 int /*<<< orphan*/  FSP_REG_SWC1 ; 
 int /*<<< orphan*/  FSP_REG_SYSCTL5 ; 
 scalar_t__ FSP_VER_STL3888_C0 ; 
 int /*<<< orphan*/  PSMOUSE_CMD_GETID ; 
 int /*<<< orphan*/  PSMOUSE_CMD_SETRATE ; 
 scalar_t__ fsp_get_buttons (struct psmouse*,int*) ; 
 int /*<<< orphan*/  fsp_onpad_hscr (struct psmouse*,int) ; 
 int /*<<< orphan*/  fsp_onpad_vscr (struct psmouse*,int) ; 
 scalar_t__ fsp_opc_tag_enable (struct psmouse*,int) ; 
 scalar_t__ fsp_reg_read (struct psmouse*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ fsp_reg_write (struct psmouse*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ps2_command (struct ps2dev*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psmouse_err (struct psmouse*,char*) ; 
 int /*<<< orphan*/  psmouse_warn (struct psmouse*,char*) ; 

__attribute__((used)) static int fsp_activate_protocol(struct psmouse *psmouse)
{
	struct fsp_data *pad = psmouse->private;
	struct ps2dev *ps2dev = &psmouse->ps2dev;
	unsigned char param[2];
	int val;

	/*
	 * Standard procedure to enter FSP Intellimouse mode
	 * (scrolling wheel, 4th and 5th buttons)
	 */
	param[0] = 200;
	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRATE);
	param[0] = 200;
	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRATE);
	param[0] =  80;
	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRATE);

	ps2_command(ps2dev, param, PSMOUSE_CMD_GETID);
	if (param[0] != 0x04) {
		psmouse_err(psmouse,
			    "Unable to enable 4 bytes packet format.\n");
		return -EIO;
	}

	if (pad->ver < FSP_VER_STL3888_C0) {
		/* Preparing relative coordinates output for older hardware */
		if (fsp_reg_read(psmouse, FSP_REG_SYSCTL5, &val)) {
			psmouse_err(psmouse,
				    "Unable to read SYSCTL5 register.\n");
			return -EIO;
		}

		if (fsp_get_buttons(psmouse, &pad->buttons)) {
			psmouse_err(psmouse,
				    "Unable to retrieve number of buttons.\n");
			return -EIO;
		}

		val &= ~(FSP_BIT_EN_MSID7 | FSP_BIT_EN_MSID8 | FSP_BIT_EN_AUTO_MSID8);
		/* Ensure we are not in absolute mode */
		val &= ~FSP_BIT_EN_PKT_G0;
		if (pad->buttons == 0x06) {
			/* Left/Middle/Right & Scroll Up/Down/Right/Left */
			val |= FSP_BIT_EN_MSID6;
		}

		if (fsp_reg_write(psmouse, FSP_REG_SYSCTL5, val)) {
			psmouse_err(psmouse,
				    "Unable to set up required mode bits.\n");
			return -EIO;
		}

		/*
		 * Enable OPC tags such that driver can tell the difference
		 * between on-pad and real button click
		 */
		if (fsp_opc_tag_enable(psmouse, true))
			psmouse_warn(psmouse,
				     "Failed to enable OPC tag mode.\n");
		/* enable on-pad click by default */
		pad->flags |= FSPDRV_FLAG_EN_OPC;

		/* Enable on-pad vertical and horizontal scrolling */
		fsp_onpad_vscr(psmouse, true);
		fsp_onpad_hscr(psmouse, true);
	} else {
		/* Enable absolute coordinates output for Cx/Dx hardware */
		if (fsp_reg_write(psmouse, FSP_REG_SWC1,
				  FSP_BIT_SWC1_EN_ABS_1F |
				  FSP_BIT_SWC1_EN_ABS_2F |
				  FSP_BIT_SWC1_EN_FUP_OUT |
				  FSP_BIT_SWC1_EN_ABS_CON)) {
			psmouse_err(psmouse,
				    "Unable to enable absolute coordinates output.\n");
			return -EIO;
		}
	}

	return 0;
}