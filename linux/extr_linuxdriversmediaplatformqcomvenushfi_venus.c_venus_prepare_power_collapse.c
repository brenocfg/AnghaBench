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
struct venus_hfi_device {int /*<<< orphan*/  pwr_collapse_prep; } ;
struct hfi_sys_pc_prep_pkt {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pkt_sys_pc_prep (struct hfi_sys_pc_prep_pkt*) ; 
 int /*<<< orphan*/  venus_flush_debug_queue (struct venus_hfi_device*) ; 
 int /*<<< orphan*/  venus_hw_rsp_timeout ; 
 int venus_iface_cmdq_write (struct venus_hfi_device*,struct hfi_sys_pc_prep_pkt*) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int venus_prepare_power_collapse(struct venus_hfi_device *hdev,
					bool wait)
{
	unsigned long timeout = msecs_to_jiffies(venus_hw_rsp_timeout);
	struct hfi_sys_pc_prep_pkt pkt;
	int ret;

	init_completion(&hdev->pwr_collapse_prep);

	pkt_sys_pc_prep(&pkt);

	ret = venus_iface_cmdq_write(hdev, &pkt);
	if (ret)
		return ret;

	if (!wait)
		return 0;

	ret = wait_for_completion_timeout(&hdev->pwr_collapse_prep, timeout);
	if (!ret) {
		venus_flush_debug_queue(hdev);
		return -ETIMEDOUT;
	}

	return 0;
}