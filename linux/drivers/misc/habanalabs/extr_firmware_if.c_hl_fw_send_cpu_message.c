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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct hl_device {int device_cpu_disabled; TYPE_1__* asic_funcs; int /*<<< orphan*/  send_cpu_message_lock; int /*<<< orphan*/  dev; scalar_t__ disabled; } ;
struct armcp_packet {int /*<<< orphan*/  result; int /*<<< orphan*/  ctl; int /*<<< orphan*/  fence; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* cpu_accessible_dma_pool_free ) (struct hl_device*,int /*<<< orphan*/ ,struct armcp_packet*) ;struct armcp_packet* (* cpu_accessible_dma_pool_alloc ) (struct hl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int ARMCP_PACKET_FENCE_VAL ; 
 int ARMCP_PKT_CTL_OPCODE_MASK ; 
 int ARMCP_PKT_CTL_OPCODE_SHIFT ; 
 int ARMCP_PKT_CTL_RC_MASK ; 
 int ARMCP_PKT_CTL_RC_SHIFT ; 
 int EIO ; 
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  hl_hw_queue_inc_ci_kernel (struct hl_device*,int) ; 
 int hl_hw_queue_send_cb_no_cmpl (struct hl_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hl_poll_timeout_memory (struct hl_device*,int /*<<< orphan*/ *,int,int,int,int,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct armcp_packet*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct armcp_packet* stub1 (struct hl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct hl_device*,int /*<<< orphan*/ ,struct armcp_packet*) ; 

int hl_fw_send_cpu_message(struct hl_device *hdev, u32 hw_queue_id, u32 *msg,
				u16 len, u32 timeout, long *result)
{
	struct armcp_packet *pkt;
	dma_addr_t pkt_dma_addr;
	u32 tmp;
	int rc = 0;

	pkt = hdev->asic_funcs->cpu_accessible_dma_pool_alloc(hdev, len,
								&pkt_dma_addr);
	if (!pkt) {
		dev_err(hdev->dev,
			"Failed to allocate DMA memory for packet to CPU\n");
		return -ENOMEM;
	}

	memcpy(pkt, msg, len);

	mutex_lock(&hdev->send_cpu_message_lock);

	if (hdev->disabled)
		goto out;

	if (hdev->device_cpu_disabled) {
		rc = -EIO;
		goto out;
	}

	rc = hl_hw_queue_send_cb_no_cmpl(hdev, hw_queue_id, len, pkt_dma_addr);
	if (rc) {
		dev_err(hdev->dev, "Failed to send CB on CPU PQ (%d)\n", rc);
		goto out;
	}

	rc = hl_poll_timeout_memory(hdev, &pkt->fence, tmp,
				(tmp == ARMCP_PACKET_FENCE_VAL), 1000,
				timeout, true);

	hl_hw_queue_inc_ci_kernel(hdev, hw_queue_id);

	if (rc == -ETIMEDOUT) {
		dev_err(hdev->dev, "Device CPU packet timeout (0x%x)\n", tmp);
		hdev->device_cpu_disabled = true;
		goto out;
	}

	tmp = le32_to_cpu(pkt->ctl);

	rc = (tmp & ARMCP_PKT_CTL_RC_MASK) >> ARMCP_PKT_CTL_RC_SHIFT;
	if (rc) {
		dev_err(hdev->dev, "F/W ERROR %d for CPU packet %d\n",
			rc,
			(tmp & ARMCP_PKT_CTL_OPCODE_MASK)
						>> ARMCP_PKT_CTL_OPCODE_SHIFT);
		rc = -EIO;
	} else if (result) {
		*result = (long) le64_to_cpu(pkt->result);
	}

out:
	mutex_unlock(&hdev->send_cpu_message_lock);

	hdev->asic_funcs->cpu_accessible_dma_pool_free(hdev, len, pkt);

	return rc;
}