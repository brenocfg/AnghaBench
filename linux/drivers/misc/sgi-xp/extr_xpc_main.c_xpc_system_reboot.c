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
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;

/* Variables and functions */
 int NOTIFY_DONE ; 
#define  SYS_HALT 130 
#define  SYS_POWER_OFF 129 
#define  SYS_RESTART 128 
 int xpSystemGoingDown ; 
 int xpSystemHalt ; 
 int xpSystemPoweroff ; 
 int xpSystemReboot ; 
 int /*<<< orphan*/  xpc_do_exit (int) ; 

__attribute__((used)) static int
xpc_system_reboot(struct notifier_block *nb, unsigned long event, void *unused)
{
	enum xp_retval reason;

	switch (event) {
	case SYS_RESTART:
		reason = xpSystemReboot;
		break;
	case SYS_HALT:
		reason = xpSystemHalt;
		break;
	case SYS_POWER_OFF:
		reason = xpSystemPoweroff;
		break;
	default:
		reason = xpSystemGoingDown;
	}

	xpc_do_exit(reason);
	return NOTIFY_DONE;
}