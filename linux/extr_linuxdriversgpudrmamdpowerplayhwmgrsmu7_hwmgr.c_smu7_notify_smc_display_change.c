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
struct pp_hwmgr {int dummy; } ;
typedef  int /*<<< orphan*/  PPSMC_Msg ;

/* Variables and functions */
 scalar_t__ PPSMC_HasDisplay ; 
 scalar_t__ PPSMC_NoDisplay ; 
 scalar_t__ smum_send_msg_to_smc (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
smu7_notify_smc_display_change(struct pp_hwmgr *hwmgr, bool has_display)
{
	PPSMC_Msg msg = has_display ? (PPSMC_Msg)PPSMC_HasDisplay : (PPSMC_Msg)PPSMC_NoDisplay;

	return (smum_send_msg_to_smc(hwmgr, msg) == 0) ?  0 : -1;
}