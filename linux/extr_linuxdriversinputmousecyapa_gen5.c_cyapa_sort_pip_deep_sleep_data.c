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
struct cyapa {int dummy; } ;

/* Variables and functions */
 int PIP_APP_DEEP_SLEEP_REPORT_ID ; 
 int PIP_DEEP_SLEEP_OPCODE ; 
 int PIP_DEEP_SLEEP_OPCODE_MASK ; 
 int PIP_DEEP_SLEEP_RESP_LENGTH ; 
 size_t PIP_RESP_REPORT_ID_OFFSET ; 

__attribute__((used)) static bool cyapa_sort_pip_deep_sleep_data(struct cyapa *cyapa,
		u8 *buf, int len)
{
	if (len == PIP_DEEP_SLEEP_RESP_LENGTH &&
		buf[PIP_RESP_REPORT_ID_OFFSET] ==
			PIP_APP_DEEP_SLEEP_REPORT_ID &&
		(buf[4] & PIP_DEEP_SLEEP_OPCODE_MASK) ==
			PIP_DEEP_SLEEP_OPCODE)
		return true;
	return false;
}