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
struct cyapa {void* state; void* gen; } ;

/* Variables and functions */
 void* CYAPA_GEN5 ; 
 void* CYAPA_STATE_GEN5_APP ; 
 void* CYAPA_STATE_GEN5_BL ; 
 void* CYAPA_STATE_NO_DEVICE ; 
 int EIO ; 
 int GEN5_APP_MAX_OUTPUT_LENGTH ; 
 int GEN5_BL_MAX_OUTPUT_LENGTH ; 
 scalar_t__ PIP_HID_APP_REPORT_ID ; 
 scalar_t__ PIP_HID_BL_REPORT_ID ; 
 int PIP_HID_DESCRIPTOR_SIZE ; 
 size_t PIP_RESP_LENGTH_OFFSET ; 
 int PIP_RESP_LENGTH_SIZE ; 
 size_t PIP_RESP_REPORT_ID_OFFSET ; 
 int cyapa_i2c_pip_read (struct cyapa*,scalar_t__*,int) ; 
 int get_unaligned_le16 (scalar_t__*) ; 

__attribute__((used)) static int gen5_hid_description_header_parse(struct cyapa *cyapa, u8 *reg_data)
{
	int length;
	u8 resp_data[32];
	int max_output_len;
	int ret;

	/* 0x20 0x00 0xF7 is Gen5 Application HID Description Header;
	 * 0x20 0x00 0xFF is Gen5 Bootloader HID Description Header.
	 *
	 * Must read HID Description content through out,
	 * otherwise Gen5 trackpad cannot response next command
	 * or report any touch or button data.
	 */
	ret = cyapa_i2c_pip_read(cyapa, resp_data,
			PIP_HID_DESCRIPTOR_SIZE);
	if (ret != PIP_HID_DESCRIPTOR_SIZE)
		return ret < 0 ? ret : -EIO;
	length = get_unaligned_le16(&resp_data[PIP_RESP_LENGTH_OFFSET]);
	max_output_len = get_unaligned_le16(&resp_data[16]);
	if (length == PIP_RESP_LENGTH_SIZE) {
		if (reg_data[PIP_RESP_REPORT_ID_OFFSET] ==
				PIP_HID_BL_REPORT_ID) {
			/*
			 * BL mode HID Description has been previously
			 * read out.
			 */
			cyapa->gen = CYAPA_GEN5;
			cyapa->state = CYAPA_STATE_GEN5_BL;
		} else {
			/*
			 * APP mode HID Description has been previously
			 * read out.
			 */
			cyapa->gen = CYAPA_GEN5;
			cyapa->state = CYAPA_STATE_GEN5_APP;
		}
	} else if (length == PIP_HID_DESCRIPTOR_SIZE &&
			resp_data[2] == PIP_HID_BL_REPORT_ID &&
			max_output_len == GEN5_BL_MAX_OUTPUT_LENGTH) {
		/* BL mode HID Description read. */
		cyapa->gen = CYAPA_GEN5;
		cyapa->state = CYAPA_STATE_GEN5_BL;
	} else if (length == PIP_HID_DESCRIPTOR_SIZE &&
			(resp_data[PIP_RESP_REPORT_ID_OFFSET] ==
				PIP_HID_APP_REPORT_ID) &&
			max_output_len == GEN5_APP_MAX_OUTPUT_LENGTH) {
		/* APP mode HID Description read. */
		cyapa->gen = CYAPA_GEN5;
		cyapa->state = CYAPA_STATE_GEN5_APP;
	} else {
		/* Should not happen!!! */
		cyapa->state = CYAPA_STATE_NO_DEVICE;
	}

	return 0;
}