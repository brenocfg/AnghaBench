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
 int BIT (int) ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  PSMOUSE_CMD_SETSCALE21 ; 
 scalar_t__ __alps_command_mode_write_reg (struct psmouse*,int) ; 
 int alps_command_mode_read_reg (struct psmouse*,int) ; 
 scalar_t__ alps_enter_command_mode (struct psmouse*) ; 
 scalar_t__ alps_exit_command_mode (struct psmouse*) ; 
 scalar_t__ alps_passthrough_mode_v3 (struct psmouse*,int,int) ; 
 scalar_t__ alps_rpt_cmd (struct psmouse*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 scalar_t__ alps_trackstick_enter_extended_mode_v3_v6 (struct psmouse*) ; 
 int /*<<< orphan*/  psmouse_dbg (struct psmouse*,char*,unsigned char*) ; 
 int /*<<< orphan*/  psmouse_err (struct psmouse*,char*) ; 
 int /*<<< orphan*/  psmouse_warn (struct psmouse*,char*) ; 

__attribute__((used)) static int alps_setup_trackstick_v3(struct psmouse *psmouse, int reg_base)
{
	int ret = 0;
	int reg_val;
	unsigned char param[4];

	/*
	 * We need to configure trackstick to report data for touchpad in
	 * extended format. And also we need to tell touchpad to expect data
	 * from trackstick in extended format. Without this configuration
	 * trackstick packets sent from touchpad are in basic format which is
	 * different from what we expect.
	 */

	if (alps_passthrough_mode_v3(psmouse, reg_base, true))
		return -EIO;

	/*
	 * E7 report for the trackstick
	 *
	 * There have been reports of failures to seem to trace back
	 * to the above trackstick check failing. When these occur
	 * this E7 report fails, so when that happens we continue
	 * with the assumption that there isn't a trackstick after
	 * all.
	 */
	if (alps_rpt_cmd(psmouse, 0, PSMOUSE_CMD_SETSCALE21, param)) {
		psmouse_warn(psmouse, "Failed to initialize trackstick (E7 report failed)\n");
		ret = -ENODEV;
	} else {
		psmouse_dbg(psmouse, "trackstick E7 report: %3ph\n", param);
		if (alps_trackstick_enter_extended_mode_v3_v6(psmouse)) {
			psmouse_err(psmouse, "Failed to enter into trackstick extended mode\n");
			ret = -EIO;
		}
	}

	if (alps_passthrough_mode_v3(psmouse, reg_base, false))
		return -EIO;

	if (ret)
		return ret;

	if (alps_enter_command_mode(psmouse))
		return -EIO;

	reg_val = alps_command_mode_read_reg(psmouse, reg_base + 0x08);
	if (reg_val == -1) {
		ret = -EIO;
	} else {
		/*
		 * Tell touchpad that trackstick is now in extended mode.
		 * If bit 1 isn't set the packet format is different.
		 */
		reg_val |= BIT(1);
		if (__alps_command_mode_write_reg(psmouse, reg_val))
			ret = -EIO;
	}

	if (alps_exit_command_mode(psmouse))
		return -EIO;

	return ret;
}