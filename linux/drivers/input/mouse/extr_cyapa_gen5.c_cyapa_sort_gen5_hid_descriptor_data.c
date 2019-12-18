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
typedef  int /*<<< orphan*/  u8 ;
struct cyapa {int dummy; } ;

/* Variables and functions */
 int GEN5_APP_MAX_OUTPUT_LENGTH ; 
 int GEN5_BL_MAX_OUTPUT_LENGTH ; 
 int /*<<< orphan*/  PIP_HID_APP_REPORT_ID ; 
 int /*<<< orphan*/  PIP_HID_BL_REPORT_ID ; 
 int PIP_HID_DESCRIPTOR_SIZE ; 
 size_t PIP_RESP_LENGTH_OFFSET ; 
 size_t PIP_RESP_REPORT_ID_OFFSET ; 
 int get_unaligned_le16 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool cyapa_sort_gen5_hid_descriptor_data(struct cyapa *cyapa,
		u8 *buf, int len)
{
	int resp_len;
	int max_output_len;

	/* Check hid descriptor. */
	if (len != PIP_HID_DESCRIPTOR_SIZE)
		return false;

	resp_len = get_unaligned_le16(&buf[PIP_RESP_LENGTH_OFFSET]);
	max_output_len = get_unaligned_le16(&buf[16]);
	if (resp_len == PIP_HID_DESCRIPTOR_SIZE) {
		if (buf[PIP_RESP_REPORT_ID_OFFSET] == PIP_HID_BL_REPORT_ID &&
				max_output_len == GEN5_BL_MAX_OUTPUT_LENGTH) {
			/* BL mode HID Descriptor */
			return true;
		} else if ((buf[PIP_RESP_REPORT_ID_OFFSET] ==
				PIP_HID_APP_REPORT_ID) &&
				max_output_len == GEN5_APP_MAX_OUTPUT_LENGTH) {
			/* APP mode HID Descriptor */
			return true;
		}
	}

	return false;
}