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
typedef  enum dbg_status { ____Placeholder_dbg_status } dbg_status ;

/* Variables and functions */
 int MAX_DBG_STATUS ; 
 char const** s_status_str ; 

const char *qed_dbg_get_status_str(enum dbg_status status)
{
	return (status <
		MAX_DBG_STATUS) ? s_status_str[status] : "Invalid debug status";
}