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
typedef  int /*<<< orphan*/  u8 ;
struct isst_if_mbox_cmd {int command; int sub_command; int /*<<< orphan*/  logical_cpu; int /*<<< orphan*/  req_data; int /*<<< orphan*/  parameter; } ;
struct isst_if_cmd_cb {int /*<<< orphan*/  (* cmd_callback ) (int /*<<< orphan*/ *,int*,int) ;} ;
struct isst_cmd {int cmd; int /*<<< orphan*/  cpu; int /*<<< orphan*/  data; int /*<<< orphan*/  param; } ;

/* Variables and functions */
 int GENMASK_ULL (int,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static void isst_mbox_resume_command(struct isst_if_cmd_cb *cb,
				     struct isst_cmd *sst_cmd)
{
	struct isst_if_mbox_cmd mbox_cmd;
	int wr_only;

	mbox_cmd.command = (sst_cmd->cmd & GENMASK_ULL(31, 16)) >> 16;
	mbox_cmd.sub_command = sst_cmd->cmd & GENMASK_ULL(15, 0);
	mbox_cmd.parameter = sst_cmd->param;
	mbox_cmd.req_data = sst_cmd->data;
	mbox_cmd.logical_cpu = sst_cmd->cpu;
	(cb->cmd_callback)((u8 *)&mbox_cmd, &wr_only, 1);
}