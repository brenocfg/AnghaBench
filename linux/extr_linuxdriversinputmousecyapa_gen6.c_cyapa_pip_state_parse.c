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
typedef  int u8 ;
struct pip_fixed_info {int family_id; int silicon_id_high; } ;
struct cyapa {int /*<<< orphan*/  state; int /*<<< orphan*/  gen; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CYAPA_GEN5 ; 
 int /*<<< orphan*/  CYAPA_GEN6 ; 
 int /*<<< orphan*/  CYAPA_STATE_GEN5_APP ; 
 int /*<<< orphan*/  CYAPA_STATE_GEN5_BL ; 
 int /*<<< orphan*/  CYAPA_STATE_GEN6_APP ; 
 int /*<<< orphan*/  CYAPA_STATE_GEN6_BL ; 
 int /*<<< orphan*/  CYAPA_STATE_NO_DEVICE ; 
 int EAGAIN ; 
 int /*<<< orphan*/  PIP_DEEP_SLEEP_STATE_ON ; 
 int PIP_HID_APP_REPORT_ID ; 
 int PIP_HID_BL_REPORT_ID ; 
 int PIP_HID_DESCRIPTOR_SIZE ; 
 size_t PIP_RESP_REPORT_ID_OFFSET ; 
 int /*<<< orphan*/  cyapa_empty_pip_output_data (struct cyapa*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int cyapa_get_pip_fixed_info (struct cyapa*,struct pip_fixed_info*,int) ; 
 int cyapa_i2c_pip_cmd_irq_sync (struct cyapa*,int*,int,int*,int*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cyapa_pip_deep_sleep (struct cyapa*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cyapa_sort_pip_hid_descriptor_data ; 
 int /*<<< orphan*/  memset (struct pip_fixed_info*,int /*<<< orphan*/ ,int) ; 

int cyapa_pip_state_parse(struct cyapa *cyapa, u8 *reg_data, int len)
{
	u8 cmd[] = { 0x01, 0x00};
	struct pip_fixed_info pip_info;
	u8 resp_data[PIP_HID_DESCRIPTOR_SIZE];
	int resp_len;
	bool is_bootloader;
	int error;

	cyapa->state = CYAPA_STATE_NO_DEVICE;

	/* Try to wake from it deep sleep state if it is. */
	cyapa_pip_deep_sleep(cyapa, PIP_DEEP_SLEEP_STATE_ON);

	/* Empty the buffer queue to get fresh data with later commands. */
	cyapa_empty_pip_output_data(cyapa, NULL, NULL, NULL);

	/*
	 * Read description info from trackpad device to determine running in
	 * APP mode or Bootloader mode.
	 */
	resp_len = PIP_HID_DESCRIPTOR_SIZE;
	error = cyapa_i2c_pip_cmd_irq_sync(cyapa,
			cmd, sizeof(cmd),
			resp_data, &resp_len,
			300,
			cyapa_sort_pip_hid_descriptor_data,
			false);
	if (error)
		return error;

	if (resp_data[PIP_RESP_REPORT_ID_OFFSET] == PIP_HID_BL_REPORT_ID)
		is_bootloader = true;
	else if (resp_data[PIP_RESP_REPORT_ID_OFFSET] == PIP_HID_APP_REPORT_ID)
		is_bootloader = false;
	else
		return -EAGAIN;

	/* Get PIP fixed information to determine Gen5 or Gen6. */
	memset(&pip_info, 0, sizeof(struct pip_fixed_info));
	error = cyapa_get_pip_fixed_info(cyapa, &pip_info, is_bootloader);
	if (error)
		return error;

	if (pip_info.family_id == 0x9B && pip_info.silicon_id_high == 0x0B) {
		cyapa->gen = CYAPA_GEN6;
		cyapa->state = is_bootloader ? CYAPA_STATE_GEN6_BL
					     : CYAPA_STATE_GEN6_APP;
	} else if (pip_info.family_id == 0x91 &&
		   pip_info.silicon_id_high == 0x02) {
		cyapa->gen = CYAPA_GEN5;
		cyapa->state = is_bootloader ? CYAPA_STATE_GEN5_BL
					     : CYAPA_STATE_GEN5_APP;
	}

	return 0;
}