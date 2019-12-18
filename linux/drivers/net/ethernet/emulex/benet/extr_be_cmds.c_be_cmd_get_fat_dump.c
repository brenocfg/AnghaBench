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
struct be_dma_mem {int size; int /*<<< orphan*/  dma; struct be_cmd_resp_get_fat* va; } ;
struct be_cmd_resp_get_fat {void* read_log_length; int /*<<< orphan*/  data_buffer; void* data_buffer_size; void* read_log_offset; void* fat_operation; int /*<<< orphan*/  hdr; } ;
struct be_cmd_req_get_fat {void* read_log_length; int /*<<< orphan*/  data_buffer; void* data_buffer_size; void* read_log_offset; void* fat_operation; int /*<<< orphan*/  hdr; } ;
struct be_adapter {int /*<<< orphan*/  mcc_lock; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUBSYSTEM_COMMON ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  OPCODE_COMMON_MANAGE_FAT ; 
 scalar_t__ RETRIEVE_FAT ; 
 int be_mcc_notify_wait (struct be_adapter*) ; 
 int /*<<< orphan*/  be_wrb_cmd_hdr_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct be_mcc_wrb*,struct be_dma_mem*) ; 
 void* cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct be_cmd_resp_get_fat* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,struct be_cmd_resp_get_fat*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (void*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct be_mcc_wrb* wrb_from_mccq (struct be_adapter*) ; 

int be_cmd_get_fat_dump(struct be_adapter *adapter, u32 buf_len, void *buf)
{
	struct be_dma_mem get_fat_cmd;
	struct be_mcc_wrb *wrb;
	struct be_cmd_req_get_fat *req;
	u32 offset = 0, total_size, buf_size,
				log_offset = sizeof(u32), payload_len;
	int status;

	if (buf_len == 0)
		return 0;

	total_size = buf_len;

	get_fat_cmd.size = sizeof(struct be_cmd_req_get_fat) + 60*1024;
	get_fat_cmd.va = dma_alloc_coherent(&adapter->pdev->dev,
					    get_fat_cmd.size,
					    &get_fat_cmd.dma, GFP_ATOMIC);
	if (!get_fat_cmd.va)
		return -ENOMEM;

	mutex_lock(&adapter->mcc_lock);

	while (total_size) {
		buf_size = min(total_size, (u32)60*1024);
		total_size -= buf_size;

		wrb = wrb_from_mccq(adapter);
		if (!wrb) {
			status = -EBUSY;
			goto err;
		}
		req = get_fat_cmd.va;

		payload_len = sizeof(struct be_cmd_req_get_fat) + buf_size;
		be_wrb_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_COMMON,
				       OPCODE_COMMON_MANAGE_FAT, payload_len,
				       wrb, &get_fat_cmd);

		req->fat_operation = cpu_to_le32(RETRIEVE_FAT);
		req->read_log_offset = cpu_to_le32(log_offset);
		req->read_log_length = cpu_to_le32(buf_size);
		req->data_buffer_size = cpu_to_le32(buf_size);

		status = be_mcc_notify_wait(adapter);
		if (!status) {
			struct be_cmd_resp_get_fat *resp = get_fat_cmd.va;

			memcpy(buf + offset,
			       resp->data_buffer,
			       le32_to_cpu(resp->read_log_length));
		} else {
			dev_err(&adapter->pdev->dev, "FAT Table Retrieve error\n");
			goto err;
		}
		offset += buf_size;
		log_offset += buf_size;
	}
err:
	dma_free_coherent(&adapter->pdev->dev, get_fat_cmd.size,
			  get_fat_cmd.va, get_fat_cmd.dma);
	mutex_unlock(&adapter->mcc_lock);
	return status;
}