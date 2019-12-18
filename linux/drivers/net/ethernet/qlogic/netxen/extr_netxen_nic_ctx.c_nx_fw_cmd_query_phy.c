#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int arg1; } ;
struct TYPE_4__ {int /*<<< orphan*/  cmd; scalar_t__ arg3; scalar_t__ arg2; scalar_t__ arg1; } ;
struct netxen_cmd_args {TYPE_1__ rsp; TYPE_2__ req; } ;
struct netxen_adapter {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  NX_CDRP_CMD_READ_PHY ; 
 scalar_t__ NX_RCODE_SUCCESS ; 
 int /*<<< orphan*/  memset (struct netxen_cmd_args*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ netxen_issue_cmd (struct netxen_adapter*,struct netxen_cmd_args*) ; 

int
nx_fw_cmd_query_phy(struct netxen_adapter *adapter, u32 reg, u32 *val)
{
	u32 rcode;
	struct netxen_cmd_args cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.req.arg1 = reg;
	cmd.req.arg2 = 0;
	cmd.req.arg3 = 0;
	cmd.req.cmd = NX_CDRP_CMD_READ_PHY;
	cmd.rsp.arg1 = 1;
	rcode = netxen_issue_cmd(adapter, &cmd);
	if (rcode != NX_RCODE_SUCCESS)
		return -EIO;

	if (val == NULL)
		return -EIO;

	*val = cmd.rsp.arg1;
	return 0;
}