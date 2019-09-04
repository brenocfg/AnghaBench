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
union drbd_state {scalar_t__ conn; scalar_t__ role; scalar_t__ disk; } ;
struct drbd_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ C_CONNECTED ; 
 scalar_t__ C_DISCONNECTING ; 
 scalar_t__ C_STARTING_SYNC_S ; 
 scalar_t__ C_STARTING_SYNC_T ; 
 scalar_t__ C_VERIFY_S ; 
 scalar_t__ C_WF_REPORT_PARAMS ; 
 scalar_t__ D_FAILED ; 
 scalar_t__ R_PRIMARY ; 

__attribute__((used)) static int cl_wide_st_chg(struct drbd_device *device,
			  union drbd_state os, union drbd_state ns)
{
	return (os.conn >= C_CONNECTED && ns.conn >= C_CONNECTED &&
		 ((os.role != R_PRIMARY && ns.role == R_PRIMARY) ||
		  (os.conn != C_STARTING_SYNC_T && ns.conn == C_STARTING_SYNC_T) ||
		  (os.conn != C_STARTING_SYNC_S && ns.conn == C_STARTING_SYNC_S) ||
		  (os.disk != D_FAILED && ns.disk == D_FAILED))) ||
		(os.conn >= C_CONNECTED && ns.conn == C_DISCONNECTING) ||
		(os.conn == C_CONNECTED && ns.conn == C_VERIFY_S) ||
		(os.conn == C_CONNECTED && ns.conn == C_WF_REPORT_PARAMS);
}