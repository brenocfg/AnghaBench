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
struct cyapa {int /*<<< orphan*/  state; int /*<<< orphan*/  gen; } ;
typedef  int /*<<< orphan*/  resp_data ;

/* Variables and functions */
 int /*<<< orphan*/  CYAPA_GEN5 ; 
 int /*<<< orphan*/  CYAPA_STATE_GEN5_APP ; 
 int /*<<< orphan*/  CYAPA_STATE_GEN5_BL ; 
 int /*<<< orphan*/  CYAPA_STATE_NO_DEVICE ; 
 int EIO ; 
 int GEN5_APP_MAX_OUTPUT_LENGTH ; 
 int GEN5_BL_MAX_OUTPUT_LENGTH ; 
 int PIP_HID_APP_REPORT_ID ; 
 int PIP_HID_BL_REPORT_ID ; 
 int PIP_HID_DESCRIPTOR_SIZE ; 
 size_t PIP_RESP_LENGTH_OFFSET ; 
 int PIP_RESP_LENGTH_SIZE ; 
 size_t PIP_RESP_REPORT_ID_OFFSET ; 
 int /*<<< orphan*/  cyapa_empty_pip_output_data (struct cyapa*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int cyapa_i2c_pip_cmd_irq_sync (struct cyapa*,int*,int,int*,int*,int,int /*<<< orphan*/ ,int) ; 
 int cyapa_i2c_pip_read (struct cyapa*,int*,int) ; 
 int /*<<< orphan*/  cyapa_sort_gen5_hid_descriptor_data ; 
 int get_unaligned_le16 (int*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gen5_idle_state_parse(struct cyapa *cyapa)
{
	u8 resp_data[PIP_HID_DESCRIPTOR_SIZE];
	int max_output_len;
	int length;
	u8 cmd[2];
	int ret;
	int error;

	/*
	 * Dump all buffered data firstly for the situation
	 * when the trackpad is just power on the cyapa go here.
	 */
	cyapa_empty_pip_output_data(cyapa, NULL, NULL, NULL);

	memset(resp_data, 0, sizeof(resp_data));
	ret = cyapa_i2c_pip_read(cyapa, resp_data, 3);
	if (ret != 3)
		return ret < 0 ? ret : -EIO;

	length = get_unaligned_le16(&resp_data[PIP_RESP_LENGTH_OFFSET]);
	if (length == PIP_RESP_LENGTH_SIZE) {
		/* Normal state of Gen5 with no data to response */
		cyapa->gen = CYAPA_GEN5;

		cyapa_empty_pip_output_data(cyapa, NULL, NULL, NULL);

		/* Read description from trackpad device */
		cmd[0] = 0x01;
		cmd[1] = 0x00;
		length = PIP_HID_DESCRIPTOR_SIZE;
		error = cyapa_i2c_pip_cmd_irq_sync(cyapa,
				cmd, PIP_RESP_LENGTH_SIZE,
				resp_data, &length,
				300,
				cyapa_sort_gen5_hid_descriptor_data,
				false);
		if (error)
			return error;

		length = get_unaligned_le16(
				&resp_data[PIP_RESP_LENGTH_OFFSET]);
		max_output_len = get_unaligned_le16(&resp_data[16]);
		if ((length == PIP_HID_DESCRIPTOR_SIZE ||
				length == PIP_RESP_LENGTH_SIZE) &&
			(resp_data[PIP_RESP_REPORT_ID_OFFSET] ==
				PIP_HID_BL_REPORT_ID) &&
			max_output_len == GEN5_BL_MAX_OUTPUT_LENGTH) {
			/* BL mode HID Description read */
			cyapa->state = CYAPA_STATE_GEN5_BL;
		} else if ((length == PIP_HID_DESCRIPTOR_SIZE ||
				length == PIP_RESP_LENGTH_SIZE) &&
			(resp_data[PIP_RESP_REPORT_ID_OFFSET] ==
				PIP_HID_APP_REPORT_ID) &&
			max_output_len == GEN5_APP_MAX_OUTPUT_LENGTH) {
			/* APP mode HID Description read */
			cyapa->state = CYAPA_STATE_GEN5_APP;
		} else {
			/* Should not happen!!! */
			cyapa->state = CYAPA_STATE_NO_DEVICE;
		}
	}

	return 0;
}