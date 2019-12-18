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
struct psmouse {struct cytp_data* private; } ;
struct cytp_data {unsigned char fw_version; int tp_metrics_supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  CYTP_CMD_READ_CYPRESS_ID ; 
 int ENODEV ; 
 unsigned char FW_VERSION_MASX ; 
 unsigned char TP_METRICS_MASK ; 
 scalar_t__ cypress_send_ext_cmd (struct psmouse*,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  psmouse_dbg (struct psmouse*,char*,int) ; 

__attribute__((used)) static int cypress_read_fw_version(struct psmouse *psmouse)
{
	struct cytp_data *cytp = psmouse->private;
	unsigned char param[3];

	if (cypress_send_ext_cmd(psmouse, CYTP_CMD_READ_CYPRESS_ID, param))
		return -ENODEV;

	/* Check for Cypress Trackpad signature bytes: 0x33 0xCC */
	if (param[0] != 0x33 || param[1] != 0xCC)
		return -ENODEV;

	cytp->fw_version = param[2] & FW_VERSION_MASX;
	cytp->tp_metrics_supported = (param[2] & TP_METRICS_MASK) ? 1 : 0;

	/*
	 * Trackpad fw_version 11 (in Dell XPS12) yields a bogus response to
	 * CYTP_CMD_READ_TP_METRICS so do not try to use it. LP: #1103594.
	 */
	if (cytp->fw_version >= 11)
		cytp->tp_metrics_supported = 0;

	psmouse_dbg(psmouse, "cytp->fw_version = %d\n", cytp->fw_version);
	psmouse_dbg(psmouse, "cytp->tp_metrics_supported = %d\n",
		 cytp->tp_metrics_supported);

	return 0;
}