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
union nvme_result {int /*<<< orphan*/  u64; } ;
typedef  int /*<<< orphan*/  u32 ;
struct nvme_ctrl {int /*<<< orphan*/  device; int /*<<< orphan*/  fabrics_q; } ;
struct TYPE_2__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  fctype; int /*<<< orphan*/  opcode; } ;
struct nvme_command {TYPE_1__ prop_get; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_QID_ANY ; 
 int NVME_SC_DNR ; 
 int __nvme_submit_sync_cmd (int /*<<< orphan*/ ,struct nvme_command*,union nvme_result*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct nvme_command*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvme_fabrics_command ; 
 int /*<<< orphan*/  nvme_fabrics_type_property_get ; 
 scalar_t__ unlikely (int) ; 

int nvmf_reg_read32(struct nvme_ctrl *ctrl, u32 off, u32 *val)
{
	struct nvme_command cmd;
	union nvme_result res;
	int ret;

	memset(&cmd, 0, sizeof(cmd));
	cmd.prop_get.opcode = nvme_fabrics_command;
	cmd.prop_get.fctype = nvme_fabrics_type_property_get;
	cmd.prop_get.offset = cpu_to_le32(off);

	ret = __nvme_submit_sync_cmd(ctrl->fabrics_q, &cmd, &res, NULL, 0, 0,
			NVME_QID_ANY, 0, 0, false);

	if (ret >= 0)
		*val = le64_to_cpu(res.u64);
	if (unlikely(ret != 0))
		dev_err(ctrl->device,
			"Property Get error: %d, offset %#x\n",
			ret > 0 ? ret & ~NVME_SC_DNR : ret, off);

	return ret;
}