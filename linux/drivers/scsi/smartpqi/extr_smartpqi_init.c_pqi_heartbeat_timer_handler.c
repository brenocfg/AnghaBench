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
typedef  scalar_t__ u32 ;
struct timer_list {int dummy; } ;
struct pqi_ctrl_info {int previous_num_interrupts; scalar_t__ previous_heartbeat_count; int /*<<< orphan*/  heartbeat_timer; TYPE_1__* pci_dev; int /*<<< orphan*/  num_interrupts; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ PQI_HEARTBEAT_TIMER_INTERVAL ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct pqi_ctrl_info* ctrl_info ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 struct pqi_ctrl_info* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heartbeat_timer ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pqi_check_ctrl_health (struct pqi_ctrl_info*) ; 
 scalar_t__ pqi_ctrl_offline (struct pqi_ctrl_info*) ; 
 scalar_t__ pqi_read_heartbeat_counter (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_take_ctrl_offline (struct pqi_ctrl_info*) ; 

__attribute__((used)) static void pqi_heartbeat_timer_handler(struct timer_list *t)
{
	int num_interrupts;
	u32 heartbeat_count;
	struct pqi_ctrl_info *ctrl_info = from_timer(ctrl_info, t,
						     heartbeat_timer);

	pqi_check_ctrl_health(ctrl_info);
	if (pqi_ctrl_offline(ctrl_info))
		return;

	num_interrupts = atomic_read(&ctrl_info->num_interrupts);
	heartbeat_count = pqi_read_heartbeat_counter(ctrl_info);

	if (num_interrupts == ctrl_info->previous_num_interrupts) {
		if (heartbeat_count == ctrl_info->previous_heartbeat_count) {
			dev_err(&ctrl_info->pci_dev->dev,
				"no heartbeat detected - last heartbeat count: %u\n",
				heartbeat_count);
			pqi_take_ctrl_offline(ctrl_info);
			return;
		}
	} else {
		ctrl_info->previous_num_interrupts = num_interrupts;
	}

	ctrl_info->previous_heartbeat_count = heartbeat_count;
	mod_timer(&ctrl_info->heartbeat_timer,
		jiffies + PQI_HEARTBEAT_TIMER_INTERVAL);
}