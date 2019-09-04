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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 unsigned int CPC_Cx_STAT_CONF_EJTAG_PROBE ; 
 int NOTIFY_BAD ; 
 int NOTIFY_DONE ; 
#define  PM_SUSPEND_PREPARE 128 
 int /*<<< orphan*/  pr_warn (char*) ; 
 unsigned int read_cpc_cl_stat_conf () ; 

__attribute__((used)) static int cps_pm_power_notifier(struct notifier_block *this,
				 unsigned long event, void *ptr)
{
	unsigned int stat;

	switch (event) {
	case PM_SUSPEND_PREPARE:
		stat = read_cpc_cl_stat_conf();
		/*
		 * If we're attempting to suspend the system and power down all
		 * of the cores, the JTAG detect bit indicates that the CPC will
		 * instead put the cores into clock-off state. In this state
		 * a connected debugger can cause the CPU to attempt
		 * interactions with the powered down system. At best this will
		 * fail. At worst, it can hang the NoC, requiring a hard reset.
		 * To avoid this, just block system suspend if a JTAG probe
		 * is detected.
		 */
		if (stat & CPC_Cx_STAT_CONF_EJTAG_PROBE) {
			pr_warn("JTAG probe is connected - abort suspend\n");
			return NOTIFY_BAD;
		}
		return NOTIFY_DONE;
	default:
		return NOTIFY_DONE;
	}
}