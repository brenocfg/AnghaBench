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
struct alps_protocol_info {int dummy; } ;
struct alps_data {int /*<<< orphan*/  fw_ver; int /*<<< orphan*/  dev_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  PSMOUSE_CMD_RESET_WRAP ; 
 int /*<<< orphan*/  PSMOUSE_CMD_SETRES ; 
 int /*<<< orphan*/  PSMOUSE_CMD_SETSCALE11 ; 
 int /*<<< orphan*/  PSMOUSE_CMD_SETSCALE21 ; 
 scalar_t__ alps_exit_command_mode (struct psmouse*) ; 
 struct alps_protocol_info* alps_match_table (unsigned char*,unsigned char*) ; 
 scalar_t__ alps_rpt_cmd (struct psmouse*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 int alps_set_protocol (struct psmouse*,struct alps_data*,struct alps_protocol_info const*) ; 
 struct alps_protocol_info alps_v3_protocol_data ; 
 struct alps_protocol_info alps_v3_rushmore_data ; 
 struct alps_protocol_info alps_v4_protocol_data ; 
 struct alps_protocol_info alps_v5_protocol_data ; 
 struct alps_protocol_info alps_v7_protocol_data ; 
 struct alps_protocol_info alps_v8_protocol_data ; 
 struct alps_protocol_info alps_v9_protocol_data ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  psmouse_dbg (struct psmouse*,char*,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  psmouse_warn (struct psmouse*,char*,unsigned char*,unsigned char*) ; 

__attribute__((used)) static int alps_identify(struct psmouse *psmouse, struct alps_data *priv)
{
	const struct alps_protocol_info *protocol;
	unsigned char e6[4], e7[4], ec[4];
	int error;

	/*
	 * First try "E6 report".
	 * ALPS should return 0,0,10 or 0,0,100 if no buttons are pressed.
	 * The bits 0-2 of the first byte will be 1s if some buttons are
	 * pressed.
	 */
	if (alps_rpt_cmd(psmouse, PSMOUSE_CMD_SETRES,
			 PSMOUSE_CMD_SETSCALE11, e6))
		return -EIO;

	if ((e6[0] & 0xf8) != 0 || e6[1] != 0 || (e6[2] != 10 && e6[2] != 100))
		return -EINVAL;

	/*
	 * Now get the "E7" and "EC" reports.  These will uniquely identify
	 * most ALPS touchpads.
	 */
	if (alps_rpt_cmd(psmouse, PSMOUSE_CMD_SETRES,
			 PSMOUSE_CMD_SETSCALE21, e7) ||
	    alps_rpt_cmd(psmouse, PSMOUSE_CMD_SETRES,
			 PSMOUSE_CMD_RESET_WRAP, ec) ||
	    alps_exit_command_mode(psmouse))
		return -EIO;

	protocol = alps_match_table(e7, ec);
	if (!protocol) {
		if (e7[0] == 0x73 && e7[1] == 0x02 && e7[2] == 0x64 &&
			   ec[2] == 0x8a) {
			protocol = &alps_v4_protocol_data;
		} else if (e7[0] == 0x73 && e7[1] == 0x03 && e7[2] == 0x50 &&
			   ec[0] == 0x73 && (ec[1] == 0x01 || ec[1] == 0x02)) {
			protocol = &alps_v5_protocol_data;
		} else if (ec[0] == 0x88 &&
			   ((ec[1] & 0xf0) == 0xb0 || (ec[1] & 0xf0) == 0xc0)) {
			protocol = &alps_v7_protocol_data;
		} else if (ec[0] == 0x88 && ec[1] == 0x08) {
			protocol = &alps_v3_rushmore_data;
		} else if (ec[0] == 0x88 && ec[1] == 0x07 &&
			   ec[2] >= 0x90 && ec[2] <= 0x9d) {
			protocol = &alps_v3_protocol_data;
		} else if (e7[0] == 0x73 && e7[1] == 0x03 &&
			   (e7[2] == 0x14 || e7[2] == 0x28)) {
			protocol = &alps_v8_protocol_data;
		} else if (e7[0] == 0x73 && e7[1] == 0x03 && e7[2] == 0xc8) {
			protocol = &alps_v9_protocol_data;
			psmouse_warn(psmouse,
				     "Unsupported ALPS V9 touchpad: E7=%3ph, EC=%3ph\n",
				     e7, ec);
			return -EINVAL;
		} else {
			psmouse_dbg(psmouse,
				    "Likely not an ALPS touchpad: E7=%3ph, EC=%3ph\n", e7, ec);
			return -EINVAL;
		}
	}

	if (priv) {
		/* Save Device ID and Firmware version */
		memcpy(priv->dev_id, e7, 3);
		memcpy(priv->fw_ver, ec, 3);
		error = alps_set_protocol(psmouse, priv, protocol);
		if (error)
			return error;
	}

	return 0;
}