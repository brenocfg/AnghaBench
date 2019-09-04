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
typedef  unsigned long uint64_t ;
struct opal_msg {int /*<<< orphan*/ * params; } ;
struct notifier_block {int dummy; } ;

/* Variables and functions */
#define  OPAL_MSG_DPO 132 
#define  OPAL_MSG_EPOW 131 
#define  OPAL_MSG_SHUTDOWN 130 
#define  SOFT_OFF 129 
#define  SOFT_REBOOT 128 
 unsigned long be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  detect_epow () ; 
 int /*<<< orphan*/  orderly_poweroff (int) ; 
 int /*<<< orphan*/  orderly_reboot () ; 
 int /*<<< orphan*/  pr_err (char*,unsigned long) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static int opal_power_control_event(struct notifier_block *nb,
					unsigned long msg_type, void *msg)
{
	uint64_t type;

	switch (msg_type) {
	case OPAL_MSG_EPOW:
		if (detect_epow()) {
			pr_info("EPOW msg received. Powering off system\n");
			orderly_poweroff(true);
		}
		break;
	case OPAL_MSG_DPO:
		pr_info("DPO msg received. Powering off system\n");
		orderly_poweroff(true);
		break;
	case OPAL_MSG_SHUTDOWN:
		type = be64_to_cpu(((struct opal_msg *)msg)->params[0]);
		switch (type) {
		case SOFT_REBOOT:
			pr_info("Reboot requested\n");
			orderly_reboot();
			break;
		case SOFT_OFF:
			pr_info("Poweroff requested\n");
			orderly_poweroff(true);
			break;
		default:
			pr_err("Unknown power-control type %llu\n", type);
		}
		break;
	default:
		pr_err("Unknown OPAL message type %lu\n", msg_type);
	}

	return 0;
}