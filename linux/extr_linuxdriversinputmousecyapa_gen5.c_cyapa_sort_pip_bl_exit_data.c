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
 int PIP_BL_FAIL_EXIT_RESP_LEN ; 
 scalar_t__ PIP_BL_RESP_REPORT_ID ; 
 scalar_t__ PIP_EOP_KEY ; 
 size_t PIP_RESP_BL_SOP_OFFSET ; 
 int PIP_RESP_LENGTH_SIZE ; 
 size_t PIP_RESP_REPORT_ID_OFFSET ; 
 scalar_t__ PIP_RESP_RSVD_KEY ; 
 size_t PIP_RESP_RSVD_OFFSET ; 
 scalar_t__ PIP_SOP_KEY ; 

__attribute__((used)) static bool cyapa_sort_pip_bl_exit_data(struct cyapa *cyapa, u8 *buf, int len)
{
	if (buf == NULL || len < PIP_RESP_LENGTH_SIZE)
		return false;

	if (buf[0] == 0 && buf[1] == 0)
		return true;

	/* Exit bootloader failed for some reason. */
	if (len == PIP_BL_FAIL_EXIT_RESP_LEN &&
			buf[PIP_RESP_REPORT_ID_OFFSET] ==
				PIP_BL_RESP_REPORT_ID &&
			buf[PIP_RESP_RSVD_OFFSET] == PIP_RESP_RSVD_KEY &&
			buf[PIP_RESP_BL_SOP_OFFSET] == PIP_SOP_KEY &&
			buf[10] == PIP_EOP_KEY)
		return true;

	return false;
}