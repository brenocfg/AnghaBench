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
 scalar_t__ PIP_BL_RESP_REPORT_ID ; 
 int PIP_MIN_BL_RESP_LENGTH ; 
 size_t PIP_RESP_BL_SOP_OFFSET ; 
 size_t PIP_RESP_REPORT_ID_OFFSET ; 
 scalar_t__ PIP_RESP_RSVD_KEY ; 
 size_t PIP_RESP_RSVD_OFFSET ; 
 scalar_t__ PIP_SOP_KEY ; 

bool cyapa_sort_tsg_pip_bl_resp_data(struct cyapa *cyapa,
		u8 *data, int len)
{
	if (!data || len < PIP_MIN_BL_RESP_LENGTH)
		return false;

	/* Bootloader input report id 30h */
	if (data[PIP_RESP_REPORT_ID_OFFSET] == PIP_BL_RESP_REPORT_ID &&
			data[PIP_RESP_RSVD_OFFSET] == PIP_RESP_RSVD_KEY &&
			data[PIP_RESP_BL_SOP_OFFSET] == PIP_SOP_KEY)
		return true;

	return false;
}