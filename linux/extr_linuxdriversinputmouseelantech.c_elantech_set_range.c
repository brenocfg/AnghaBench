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
struct psmouse {struct elantech_data* private; } ;
struct elantech_device_info {int hw_version; int fw_version; unsigned char* capabilities; int /*<<< orphan*/  (* send_cmd ) (struct psmouse*,int /*<<< orphan*/ ,unsigned char*) ;} ;
struct elantech_data {struct elantech_device_info info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETP_FW_ID_QUERY ; 
 int /*<<< orphan*/  ETP_SAMPLE_QUERY ; 
 unsigned int ETP_XMAX_V1 ; 
 unsigned int ETP_XMAX_V2 ; 
 unsigned int ETP_XMIN_V1 ; 
 unsigned int ETP_XMIN_V2 ; 
 unsigned int ETP_YMAX_V1 ; 
 unsigned int ETP_YMAX_V2 ; 
 unsigned int ETP_YMIN_V1 ; 
 unsigned int ETP_YMIN_V2 ; 
 int /*<<< orphan*/  stub1 (struct psmouse*,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  stub2 (struct psmouse*,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  stub3 (struct psmouse*,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  stub4 (struct psmouse*,int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static int elantech_set_range(struct psmouse *psmouse,
			      unsigned int *x_min, unsigned int *y_min,
			      unsigned int *x_max, unsigned int *y_max,
			      unsigned int *width)
{
	struct elantech_data *etd = psmouse->private;
	struct elantech_device_info *info = &etd->info;
	unsigned char param[3];
	unsigned char traces;

	switch (info->hw_version) {
	case 1:
		*x_min = ETP_XMIN_V1;
		*y_min = ETP_YMIN_V1;
		*x_max = ETP_XMAX_V1;
		*y_max = ETP_YMAX_V1;
		break;

	case 2:
		if (info->fw_version == 0x020800 ||
		    info->fw_version == 0x020b00 ||
		    info->fw_version == 0x020030) {
			*x_min = ETP_XMIN_V2;
			*y_min = ETP_YMIN_V2;
			*x_max = ETP_XMAX_V2;
			*y_max = ETP_YMAX_V2;
		} else {
			int i;
			int fixed_dpi;

			i = (info->fw_version > 0x020800 &&
			     info->fw_version < 0x020900) ? 1 : 2;

			if (info->send_cmd(psmouse, ETP_FW_ID_QUERY, param))
				return -1;

			fixed_dpi = param[1] & 0x10;

			if (((info->fw_version >> 16) == 0x14) && fixed_dpi) {
				if (info->send_cmd(psmouse, ETP_SAMPLE_QUERY, param))
					return -1;

				*x_max = (info->capabilities[1] - i) * param[1] / 2;
				*y_max = (info->capabilities[2] - i) * param[2] / 2;
			} else if (info->fw_version == 0x040216) {
				*x_max = 819;
				*y_max = 405;
			} else if (info->fw_version == 0x040219 || info->fw_version == 0x040215) {
				*x_max = 900;
				*y_max = 500;
			} else {
				*x_max = (info->capabilities[1] - i) * 64;
				*y_max = (info->capabilities[2] - i) * 64;
			}
		}
		break;

	case 3:
		if (info->send_cmd(psmouse, ETP_FW_ID_QUERY, param))
			return -1;

		*x_max = (0x0f & param[0]) << 8 | param[1];
		*y_max = (0xf0 & param[0]) << 4 | param[2];
		break;

	case 4:
		if (info->send_cmd(psmouse, ETP_FW_ID_QUERY, param))
			return -1;

		*x_max = (0x0f & param[0]) << 8 | param[1];
		*y_max = (0xf0 & param[0]) << 4 | param[2];
		traces = info->capabilities[1];
		if ((traces < 2) || (traces > *x_max))
			return -1;

		*width = *x_max / (traces - 1);
		break;
	}

	return 0;
}