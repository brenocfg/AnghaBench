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
struct qlcnic_cmd_args {int dummy; } ;
struct qlcnic_back_channel {int /*<<< orphan*/  vf_async_work; int /*<<< orphan*/  bc_async_wq; } ;
struct qlcnic_async_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct qlcnic_cmd_args*) ; 
 int /*<<< orphan*/  qlcnic_free_mbx_args (struct qlcnic_cmd_args*) ; 
 struct qlcnic_async_cmd* qlcnic_sriov_alloc_async_cmd (struct qlcnic_back_channel*,struct qlcnic_cmd_args*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qlcnic_sriov_schedule_async_cmd(struct qlcnic_back_channel *bc,
					    struct qlcnic_cmd_args *cmd)
{
	struct qlcnic_async_cmd *entry = NULL;

	entry = qlcnic_sriov_alloc_async_cmd(bc, cmd);
	if (!entry) {
		qlcnic_free_mbx_args(cmd);
		kfree(cmd);
		return;
	}

	queue_work(bc->bc_async_wq, &bc->vf_async_work);
}