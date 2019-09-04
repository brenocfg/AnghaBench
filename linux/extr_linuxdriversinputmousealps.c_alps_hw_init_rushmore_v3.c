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
struct psmouse {struct ps2dev ps2dev; struct alps_data* private; } ;
struct alps_data {int flags; } ;

/* Variables and functions */
 int ALPS_DUALPOINT ; 
 int /*<<< orphan*/  ALPS_REG_BASE_RUSHMORE ; 
 int EIO ; 
 int /*<<< orphan*/  PSMOUSE_CMD_ENABLE ; 
 scalar_t__ __alps_command_mode_write_reg (struct psmouse*,int) ; 
 int alps_command_mode_read_reg (struct psmouse*,int) ; 
 scalar_t__ alps_command_mode_write_reg (struct psmouse*,int,int) ; 
 scalar_t__ alps_enter_command_mode (struct psmouse*) ; 
 int /*<<< orphan*/  alps_exit_command_mode (struct psmouse*) ; 
 scalar_t__ alps_get_v3_v7_resolution (struct psmouse*,int) ; 
 int alps_setup_trackstick_v3 (struct psmouse*,int /*<<< orphan*/ ) ; 
 int ps2_command (struct ps2dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alps_hw_init_rushmore_v3(struct psmouse *psmouse)
{
	struct alps_data *priv = psmouse->private;
	struct ps2dev *ps2dev = &psmouse->ps2dev;
	int reg_val, ret = -1;

	if (priv->flags & ALPS_DUALPOINT) {
		reg_val = alps_setup_trackstick_v3(psmouse,
						   ALPS_REG_BASE_RUSHMORE);
		if (reg_val == -EIO)
			goto error;
	}

	if (alps_enter_command_mode(psmouse) ||
	    alps_command_mode_read_reg(psmouse, 0xc2d9) == -1 ||
	    alps_command_mode_write_reg(psmouse, 0xc2cb, 0x00))
		goto error;

	if (alps_get_v3_v7_resolution(psmouse, 0xc2da))
		goto error;

	reg_val = alps_command_mode_read_reg(psmouse, 0xc2c6);
	if (reg_val == -1)
		goto error;
	if (__alps_command_mode_write_reg(psmouse, reg_val & 0xfd))
		goto error;

	if (alps_command_mode_write_reg(psmouse, 0xc2c9, 0x64))
		goto error;

	/* enter absolute mode */
	reg_val = alps_command_mode_read_reg(psmouse, 0xc2c4);
	if (reg_val == -1)
		goto error;
	if (__alps_command_mode_write_reg(psmouse, reg_val | 0x02))
		goto error;

	alps_exit_command_mode(psmouse);
	return ps2_command(ps2dev, NULL, PSMOUSE_CMD_ENABLE);

error:
	alps_exit_command_mode(psmouse);
	return ret;
}