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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ bfa_fcs_rport_max_logins ; 

void
bfa_fcs_rport_set_max_logins(u32 max_logins)
{
	if (max_logins > 0)
		bfa_fcs_rport_max_logins = max_logins;
}