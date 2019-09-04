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
struct cyapa {int dummy; } ;

/* Variables and functions */
 scalar_t__ PIP_HID_APP_REPORT_ID ; 
 scalar_t__ PIP_HID_BL_REPORT_ID ; 
 int PIP_HID_DESCRIPTOR_SIZE ; 
 size_t PIP_RESP_REPORT_ID_OFFSET ; 

__attribute__((used)) static bool cyapa_sort_pip_hid_descriptor_data(struct cyapa *cyapa,
		u8 *buf, int len)
{
	if (len != PIP_HID_DESCRIPTOR_SIZE)
		return false;

	if (buf[PIP_RESP_REPORT_ID_OFFSET] == PIP_HID_APP_REPORT_ID ||
		buf[PIP_RESP_REPORT_ID_OFFSET] == PIP_HID_BL_REPORT_ID)
		return true;

	return false;
}