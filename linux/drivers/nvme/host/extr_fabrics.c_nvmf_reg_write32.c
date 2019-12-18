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
typedef  int /*<<< orphan*/  u32 ;
struct nvme_ctrl {int /*<<< orphan*/  device; int /*<<< orphan*/  fabrics_q; } ;
struct TYPE_2__ {int /*<<< orphan*/  value; int /*<<< orphan*/  offset; scalar_t__ attrib; int /*<<< orphan*/  fctype; int /*<<< orphan*/  opcode; } ;
struct nvme_command {TYPE_1__ prop_set; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_QID_ANY ; 
 int NVME_SC_DNR ; 
 int __nvme_submit_sync_cmd (int /*<<< orphan*/ ,struct nvme_command*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct nvme_command*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvme_fabrics_command ; 
 int /*<<< orphan*/  nvme_fabrics_type_property_set ; 
 scalar_t__ unlikely (int) ; 

int nvmf_reg_write32(struct nvme_ctrl *ctrl, u32 off, u32 val)
{
	struct nvme_command cmd;
	int ret;

	memset(&cmd, 0, sizeof(cmd));
	cmd.prop_set.opcode = nvme_fabrics_command;
	cmd.prop_set.fctype = nvme_fabrics_type_property_set;
	cmd.prop_set.attrib = 0;
	cmd.prop_set.offset = cpu_to_le32(off);
	cmd.prop_set.value = cpu_to_le64(val);

	ret = __nvme_submit_sync_cmd(ctrl->fabrics_q, &cmd, NULL, NULL, 0, 0,
			NVME_QID_ANY, 0, 0, false);
	if (unlikely(ret))
		dev_err(ctrl->device,
			"Property Set error: %d, offset %#x\n",
			ret > 0 ? ret & ~NVME_SC_DNR : ret, off);
	return ret;
}