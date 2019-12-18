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
struct cytp_data {int tp_width; int tp_high; int tp_max_abs_x; int tp_max_abs_y; unsigned char tp_min_pressure; unsigned char tp_max_pressure; int tp_res_x; int tp_res_y; int /*<<< orphan*/  tp_metrics_supported; } ;
typedef  int /*<<< orphan*/  param ;

/* Variables and functions */
 int CYTP_ABS_MAX_X ; 
 int CYTP_ABS_MAX_Y ; 
 int /*<<< orphan*/  CYTP_CMD_READ_TP_METRICS ; 
 int CYTP_DEFAULT_HIGH ; 
 int CYTP_DEFAULT_WIDTH ; 
 unsigned char CYTP_MAX_PRESSURE ; 
 unsigned char CYTP_MIN_PRESSURE ; 
 int EINVAL ; 
 unsigned char TP_METRICS_BIT_1F_JITTER ; 
 unsigned char TP_METRICS_BIT_1F_SPIKE ; 
 unsigned char TP_METRICS_BIT_2F_JITTER ; 
 unsigned char TP_METRICS_BIT_2F_SPIKE ; 
 unsigned char TP_METRICS_BIT_ABS_PKT_FORMAT_SET ; 
 unsigned char TP_METRICS_BIT_APA ; 
 unsigned char TP_METRICS_BIT_MTG ; 
 unsigned char TP_METRICS_BIT_PALM ; 
 unsigned char TP_METRICS_BIT_STUBBORN ; 
 scalar_t__ cypress_send_ext_cmd (struct psmouse*,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  psmouse_dbg (struct psmouse*,char*,...) ; 

__attribute__((used)) static int cypress_read_tp_metrics(struct psmouse *psmouse)
{
	struct cytp_data *cytp = psmouse->private;
	unsigned char param[8];

	/* set default values for tp metrics. */
	cytp->tp_width = CYTP_DEFAULT_WIDTH;
	cytp->tp_high = CYTP_DEFAULT_HIGH;
	cytp->tp_max_abs_x = CYTP_ABS_MAX_X;
	cytp->tp_max_abs_y = CYTP_ABS_MAX_Y;
	cytp->tp_min_pressure = CYTP_MIN_PRESSURE;
	cytp->tp_max_pressure = CYTP_MAX_PRESSURE;
	cytp->tp_res_x = cytp->tp_max_abs_x / cytp->tp_width;
	cytp->tp_res_y = cytp->tp_max_abs_y / cytp->tp_high;

	if (!cytp->tp_metrics_supported)
		return 0;

	memset(param, 0, sizeof(param));
	if (cypress_send_ext_cmd(psmouse, CYTP_CMD_READ_TP_METRICS, param) == 0) {
		/* Update trackpad parameters. */
		cytp->tp_max_abs_x = (param[1] << 8) | param[0];
		cytp->tp_max_abs_y = (param[3] << 8) | param[2];
		cytp->tp_min_pressure = param[4];
		cytp->tp_max_pressure = param[5];
	}

	if (!cytp->tp_max_pressure ||
	    cytp->tp_max_pressure < cytp->tp_min_pressure ||
	    !cytp->tp_width || !cytp->tp_high ||
	    !cytp->tp_max_abs_x ||
	    cytp->tp_max_abs_x < cytp->tp_width ||
	    !cytp->tp_max_abs_y ||
	    cytp->tp_max_abs_y < cytp->tp_high)
		return -EINVAL;

	cytp->tp_res_x = cytp->tp_max_abs_x / cytp->tp_width;
	cytp->tp_res_y = cytp->tp_max_abs_y / cytp->tp_high;

#ifdef CYTP_DEBUG_VERBOSE
	psmouse_dbg(psmouse, "Dump trackpad hardware configuration as below:\n");
	psmouse_dbg(psmouse, "cytp->tp_width = %d\n", cytp->tp_width);
	psmouse_dbg(psmouse, "cytp->tp_high = %d\n", cytp->tp_high);
	psmouse_dbg(psmouse, "cytp->tp_max_abs_x = %d\n", cytp->tp_max_abs_x);
	psmouse_dbg(psmouse, "cytp->tp_max_abs_y = %d\n", cytp->tp_max_abs_y);
	psmouse_dbg(psmouse, "cytp->tp_min_pressure = %d\n", cytp->tp_min_pressure);
	psmouse_dbg(psmouse, "cytp->tp_max_pressure = %d\n", cytp->tp_max_pressure);
	psmouse_dbg(psmouse, "cytp->tp_res_x = %d\n", cytp->tp_res_x);
	psmouse_dbg(psmouse, "cytp->tp_res_y = %d\n", cytp->tp_res_y);

	psmouse_dbg(psmouse, "tp_type_APA = %d\n",
			(param[6] & TP_METRICS_BIT_APA) ? 1 : 0);
	psmouse_dbg(psmouse, "tp_type_MTG = %d\n",
			(param[6] & TP_METRICS_BIT_MTG) ? 1 : 0);
	psmouse_dbg(psmouse, "tp_palm = %d\n",
			(param[6] & TP_METRICS_BIT_PALM) ? 1 : 0);
	psmouse_dbg(psmouse, "tp_stubborn = %d\n",
			(param[6] & TP_METRICS_BIT_STUBBORN) ? 1 : 0);
	psmouse_dbg(psmouse, "tp_1f_jitter = %d\n",
			(param[6] & TP_METRICS_BIT_1F_JITTER) >> 2);
	psmouse_dbg(psmouse, "tp_2f_jitter = %d\n",
			(param[6] & TP_METRICS_BIT_2F_JITTER) >> 4);
	psmouse_dbg(psmouse, "tp_1f_spike = %d\n",
			param[7] & TP_METRICS_BIT_1F_SPIKE);
	psmouse_dbg(psmouse, "tp_2f_spike = %d\n",
			(param[7] & TP_METRICS_BIT_2F_SPIKE) >> 2);
	psmouse_dbg(psmouse, "tp_abs_packet_format_set = %d\n",
			(param[7] & TP_METRICS_BIT_ABS_PKT_FORMAT_SET) >> 4);
#endif

	return 0;
}