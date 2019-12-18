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
struct hns_roce_dev {int is_reset; int dis_db; } ;

/* Variables and functions */
 int CMD_RST_PRC_EBUSY ; 
 int CMD_RST_PRC_SUCCESS ; 
 unsigned long HNS_ROCE_STATE_INIT ; 
 unsigned long HNS_ROCE_STATE_RST_INIT ; 

__attribute__((used)) static int hns_roce_v2_cmd_hw_reseted(struct hns_roce_dev *hr_dev,
				      unsigned long instance_stage,
				      unsigned long reset_stage)
{
	/* When hardware reset has been completed once or more, we should stop
	 * sending mailbox&cmq&doorbell to hardware. If now in .init_instance()
	 * function, we should exit with error. If now at HNAE3_INIT_CLIENT
	 * stage of soft reset process, we should exit with error, and then
	 * HNAE3_INIT_CLIENT related process can rollback the operation like
	 * notifing hardware to free resources, HNAE3_INIT_CLIENT related
	 * process will exit with error to notify NIC driver to reschedule soft
	 * reset process once again.
	 */
	hr_dev->is_reset = true;
	hr_dev->dis_db = true;

	if (reset_stage == HNS_ROCE_STATE_RST_INIT ||
	    instance_stage == HNS_ROCE_STATE_INIT)
		return CMD_RST_PRC_EBUSY;

	return CMD_RST_PRC_SUCCESS;
}