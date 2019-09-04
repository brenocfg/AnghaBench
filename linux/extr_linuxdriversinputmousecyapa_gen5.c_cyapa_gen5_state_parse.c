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
typedef  scalar_t__ u8 ;
struct cyapa {scalar_t__ state; scalar_t__ gen; } ;

/* Variables and functions */
 scalar_t__ CYAPA_GEN5 ; 
 scalar_t__ CYAPA_STATE_GEN5_APP ; 
 scalar_t__ CYAPA_STATE_GEN5_BL ; 
 scalar_t__ CYAPA_STATE_NO_DEVICE ; 
 int EAGAIN ; 
 int EINVAL ; 
 int GEN5_APP_CONTRACT_REPORT_DESCRIPTOR_SIZE ; 
 scalar_t__ GEN5_APP_REPORT_DESCRIPTOR_ID ; 
 int GEN5_APP_REPORT_DESCRIPTOR_SIZE ; 
 scalar_t__ GEN5_BL_REPORT_DESCRIPTOR_ID ; 
 int GEN5_BL_REPORT_DESCRIPTOR_SIZE ; 
 scalar_t__ GEN5_OLD_PUSH_BTN_REPORT_ID ; 
 scalar_t__ PIP_APP_RESP_REPORT_ID ; 
 scalar_t__ PIP_BL_RESP_REPORT_ID ; 
 scalar_t__ PIP_BTN_REPORT_ID ; 
 scalar_t__ PIP_HID_APP_REPORT_ID ; 
 scalar_t__ PIP_HID_BL_REPORT_ID ; 
 int PIP_HID_DESCRIPTOR_SIZE ; 
 scalar_t__ PIP_PUSH_BTN_REPORT_ID ; 
 size_t PIP_RESP_LENGTH_OFFSET ; 
 int PIP_RESP_LENGTH_SIZE ; 
 scalar_t__ PIP_TOUCH_REPORT_ID ; 
 scalar_t__ PIP_WAKEUP_EVENT_REPORT_ID ; 
 int /*<<< orphan*/  cyapa_empty_pip_output_data (struct cyapa*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen5_cmd_resp_header_parse (struct cyapa*,scalar_t__*) ; 
 int /*<<< orphan*/  gen5_hid_description_header_parse (struct cyapa*,scalar_t__*) ; 
 int /*<<< orphan*/  gen5_idle_state_parse (struct cyapa*) ; 
 int /*<<< orphan*/  gen5_report_data_header_parse (struct cyapa*,scalar_t__*) ; 
 int get_unaligned_le16 (scalar_t__*) ; 

__attribute__((used)) static int cyapa_gen5_state_parse(struct cyapa *cyapa, u8 *reg_data, int len)
{
	int length;

	if (!reg_data || len < 3)
		return -EINVAL;

	cyapa->state = CYAPA_STATE_NO_DEVICE;

	/* Parse based on Gen5 characteristic registers and bits */
	length = get_unaligned_le16(&reg_data[PIP_RESP_LENGTH_OFFSET]);
	if (length == 0 || length == PIP_RESP_LENGTH_SIZE) {
		gen5_idle_state_parse(cyapa);
	} else if (length == PIP_HID_DESCRIPTOR_SIZE &&
			(reg_data[2] == PIP_HID_BL_REPORT_ID ||
				reg_data[2] == PIP_HID_APP_REPORT_ID)) {
		gen5_hid_description_header_parse(cyapa, reg_data);
	} else if ((length == GEN5_APP_REPORT_DESCRIPTOR_SIZE ||
			length == GEN5_APP_CONTRACT_REPORT_DESCRIPTOR_SIZE) &&
			reg_data[2] == GEN5_APP_REPORT_DESCRIPTOR_ID) {
		/* 0xEE 0x00 0xF6 is Gen5 APP report description header. */
		cyapa->gen = CYAPA_GEN5;
		cyapa->state = CYAPA_STATE_GEN5_APP;
	} else if (length == GEN5_BL_REPORT_DESCRIPTOR_SIZE &&
			reg_data[2] == GEN5_BL_REPORT_DESCRIPTOR_ID) {
		/* 0x1D 0x00 0xFE is Gen5 BL report descriptor header. */
		cyapa->gen = CYAPA_GEN5;
		cyapa->state = CYAPA_STATE_GEN5_BL;
	} else if (reg_data[2] == PIP_TOUCH_REPORT_ID ||
			reg_data[2] == PIP_BTN_REPORT_ID ||
			reg_data[2] == GEN5_OLD_PUSH_BTN_REPORT_ID ||
			reg_data[2] == PIP_PUSH_BTN_REPORT_ID ||
			reg_data[2] == PIP_WAKEUP_EVENT_REPORT_ID) {
		gen5_report_data_header_parse(cyapa, reg_data);
	} else if (reg_data[2] == PIP_BL_RESP_REPORT_ID ||
			reg_data[2] == PIP_APP_RESP_REPORT_ID) {
		gen5_cmd_resp_header_parse(cyapa, reg_data);
	}

	if (cyapa->gen == CYAPA_GEN5) {
		/*
		 * Must read the content (e.g.: report description and so on)
		 * from trackpad device throughout. Otherwise,
		 * Gen5 trackpad cannot response to next command or
		 * report any touch or button data later.
		 */
		cyapa_empty_pip_output_data(cyapa, NULL, NULL, NULL);

		if (cyapa->state == CYAPA_STATE_GEN5_APP ||
			cyapa->state == CYAPA_STATE_GEN5_BL)
			return 0;
	}

	return -EAGAIN;
}