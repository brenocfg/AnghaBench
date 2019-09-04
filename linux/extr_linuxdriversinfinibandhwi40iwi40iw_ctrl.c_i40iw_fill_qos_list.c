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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 int I40IW_MAX_USER_PRIORITY ; 
 scalar_t__ QS_HANDLE_UNKNOWN ; 

__attribute__((used)) static void i40iw_fill_qos_list(u16 *qs_list)
{
	u16 qshandle = qs_list[0];
	int i;

	for (i = 0; i < I40IW_MAX_USER_PRIORITY; i++) {
		if (qs_list[i] == QS_HANDLE_UNKNOWN)
			qs_list[i] = qshandle;
		else
			qshandle = qs_list[i];
	}
}