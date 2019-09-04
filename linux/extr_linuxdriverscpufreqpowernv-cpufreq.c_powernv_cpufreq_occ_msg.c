#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct opal_occ_msg {int type; size_t throttle_status; void* chip; } ;
struct opal_msg {int /*<<< orphan*/ * params; } ;
struct notifier_block {int dummy; } ;
struct TYPE_2__ {int restore; size_t throttle_reason; int /*<<< orphan*/  throttle; int /*<<< orphan*/ * reason; void* id; } ;

/* Variables and functions */
#define  OCC_LOAD 130 
 size_t OCC_MAX_THROTTLE_STATUS ; 
#define  OCC_RESET 129 
#define  OCC_THROTTLE 128 
 unsigned long OPAL_MSG_OCC ; 
 void* be64_to_cpu (int /*<<< orphan*/ ) ; 
 TYPE_1__* chips ; 
 int nr_chips ; 
 int occ_reset ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int throttled ; 

__attribute__((used)) static int powernv_cpufreq_occ_msg(struct notifier_block *nb,
				   unsigned long msg_type, void *_msg)
{
	struct opal_msg *msg = _msg;
	struct opal_occ_msg omsg;
	int i;

	if (msg_type != OPAL_MSG_OCC)
		return 0;

	omsg.type = be64_to_cpu(msg->params[0]);

	switch (omsg.type) {
	case OCC_RESET:
		occ_reset = true;
		pr_info("OCC (On Chip Controller - enforces hard thermal/power limits) Resetting\n");
		/*
		 * powernv_cpufreq_throttle_check() is called in
		 * target() callback which can detect the throttle state
		 * for governors like ondemand.
		 * But static governors will not call target() often thus
		 * report throttling here.
		 */
		if (!throttled) {
			throttled = true;
			pr_warn("CPU frequency is throttled for duration\n");
		}

		break;
	case OCC_LOAD:
		pr_info("OCC Loading, CPU frequency is throttled until OCC is started\n");
		break;
	case OCC_THROTTLE:
		omsg.chip = be64_to_cpu(msg->params[1]);
		omsg.throttle_status = be64_to_cpu(msg->params[2]);

		if (occ_reset) {
			occ_reset = false;
			throttled = false;
			pr_info("OCC Active, CPU frequency is no longer throttled\n");

			for (i = 0; i < nr_chips; i++) {
				chips[i].restore = true;
				schedule_work(&chips[i].throttle);
			}

			return 0;
		}

		for (i = 0; i < nr_chips; i++)
			if (chips[i].id == omsg.chip)
				break;

		if (omsg.throttle_status >= 0 &&
		    omsg.throttle_status <= OCC_MAX_THROTTLE_STATUS) {
			chips[i].throttle_reason = omsg.throttle_status;
			chips[i].reason[omsg.throttle_status]++;
		}

		if (!omsg.throttle_status)
			chips[i].restore = true;

		schedule_work(&chips[i].throttle);
	}
	return 0;
}