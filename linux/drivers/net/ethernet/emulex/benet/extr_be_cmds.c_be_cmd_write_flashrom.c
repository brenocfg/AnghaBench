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
struct be_mcc_wrb {int dummy; } ;
struct be_dma_mem {int /*<<< orphan*/  size; struct be_cmd_write_flashrom* va; } ;
struct TYPE_2__ {void* data_buf_size; void* op_code; void* offset; void* op_type; } ;
struct be_cmd_write_flashrom {TYPE_1__ params; int /*<<< orphan*/  hdr; } ;
struct be_adapter {int flash_status; int /*<<< orphan*/  mcc_lock; int /*<<< orphan*/  et_cmd_compl; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUBSYSTEM_COMMON ; 
 int EBUSY ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  OPCODE_COMMON_WRITE_FLASHROM ; 
 scalar_t__ OPTYPE_OFFSET_SPECIFIED ; 
 int be_mcc_notify (struct be_adapter*) ; 
 int /*<<< orphan*/  be_wrb_cmd_hdr_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct be_mcc_wrb*,struct be_dma_mem*) ; 
 void* cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct be_mcc_wrb* wrb_from_mccq (struct be_adapter*) ; 

__attribute__((used)) static int be_cmd_write_flashrom(struct be_adapter *adapter,
				 struct be_dma_mem *cmd, u32 flash_type,
				 u32 flash_opcode, u32 img_offset, u32 buf_size)
{
	struct be_mcc_wrb *wrb;
	struct be_cmd_write_flashrom *req;
	int status;

	mutex_lock(&adapter->mcc_lock);
	adapter->flash_status = 0;

	wrb = wrb_from_mccq(adapter);
	if (!wrb) {
		status = -EBUSY;
		goto err_unlock;
	}
	req = cmd->va;

	be_wrb_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_COMMON,
			       OPCODE_COMMON_WRITE_FLASHROM, cmd->size, wrb,
			       cmd);

	req->params.op_type = cpu_to_le32(flash_type);
	if (flash_type == OPTYPE_OFFSET_SPECIFIED)
		req->params.offset = cpu_to_le32(img_offset);

	req->params.op_code = cpu_to_le32(flash_opcode);
	req->params.data_buf_size = cpu_to_le32(buf_size);

	status = be_mcc_notify(adapter);
	if (status)
		goto err_unlock;

	mutex_unlock(&adapter->mcc_lock);

	if (!wait_for_completion_timeout(&adapter->et_cmd_compl,
					 msecs_to_jiffies(40000)))
		status = -ETIMEDOUT;
	else
		status = adapter->flash_status;

	return status;

err_unlock:
	mutex_unlock(&adapter->mcc_lock);
	return status;
}