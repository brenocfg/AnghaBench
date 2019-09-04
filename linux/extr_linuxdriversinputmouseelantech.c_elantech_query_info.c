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
struct elantech_device_info {unsigned char fw_version; int hw_version; int* capabilities; int* samples; int has_trackpoint; int x_res; int y_res; int /*<<< orphan*/  bus; scalar_t__ (* send_cmd ) (struct psmouse*,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  ETP_CAPABILITIES_QUERY ; 
 int /*<<< orphan*/  ETP_FW_VERSION_QUERY ; 
 int /*<<< orphan*/  ETP_SAMPLE_QUERY ; 
 scalar_t__ elantech_get_resolution_v4 (struct psmouse*,int*,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ elantech_set_properties (struct elantech_device_info*) ; 
 int /*<<< orphan*/  memset (struct elantech_device_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  psmouse_err (struct psmouse*,char*) ; 
 int /*<<< orphan*/  psmouse_info (struct psmouse*,char*,...) ; 
 int /*<<< orphan*/  psmouse_warn (struct psmouse*,char*) ; 
 scalar_t__ stub1 (struct psmouse*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub2 (struct psmouse*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ synaptics_send_cmd (struct psmouse*,int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static int elantech_query_info(struct psmouse *psmouse,
			       struct elantech_device_info *info)
{
	unsigned char param[3];

	memset(info, 0, sizeof(*info));

	/*
	 * Do the version query again so we can store the result
	 */
	if (synaptics_send_cmd(psmouse, ETP_FW_VERSION_QUERY, param)) {
		psmouse_err(psmouse, "failed to query firmware version.\n");
		return -EINVAL;
	}
	info->fw_version = (param[0] << 16) | (param[1] << 8) | param[2];

	if (elantech_set_properties(info)) {
		psmouse_err(psmouse, "unknown hardware version, aborting...\n");
		return -EINVAL;
	}
	psmouse_info(psmouse,
		     "assuming hardware version %d (with firmware version 0x%02x%02x%02x)\n",
		     info->hw_version, param[0], param[1], param[2]);

	if (info->send_cmd(psmouse, ETP_CAPABILITIES_QUERY,
	    info->capabilities)) {
		psmouse_err(psmouse, "failed to query capabilities.\n");
		return -EINVAL;
	}
	psmouse_info(psmouse,
		     "Synaptics capabilities query result 0x%02x, 0x%02x, 0x%02x.\n",
		     info->capabilities[0], info->capabilities[1],
		     info->capabilities[2]);

	if (info->hw_version != 1) {
		if (info->send_cmd(psmouse, ETP_SAMPLE_QUERY, info->samples)) {
			psmouse_err(psmouse, "failed to query sample data\n");
			return -EINVAL;
		}
		psmouse_info(psmouse,
			     "Elan sample query result %02x, %02x, %02x\n",
			     info->samples[0],
			     info->samples[1],
			     info->samples[2]);
	}

	if (info->samples[1] == 0x74 && info->hw_version == 0x03) {
		/*
		 * This module has a bug which makes absolute mode
		 * unusable, so let's abort so we'll be using standard
		 * PS/2 protocol.
		 */
		psmouse_info(psmouse,
			     "absolute mode broken, forcing standard PS/2 protocol\n");
		return -ENODEV;
	}

	/* The MSB indicates the presence of the trackpoint */
	info->has_trackpoint = (info->capabilities[0] & 0x80) == 0x80;

	info->x_res = 31;
	info->y_res = 31;
	if (info->hw_version == 4) {
		if (elantech_get_resolution_v4(psmouse,
					       &info->x_res,
					       &info->y_res,
					       &info->bus)) {
			psmouse_warn(psmouse,
				     "failed to query resolution data.\n");
		}
	}

	return 0;
}