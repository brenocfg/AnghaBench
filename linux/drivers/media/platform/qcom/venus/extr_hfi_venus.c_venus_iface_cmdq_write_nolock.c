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
struct venus_hfi_device {struct iface_queue* queues; int /*<<< orphan*/  last_packet_type; TYPE_1__* core; } ;
struct iface_queue {int dummy; } ;
struct hfi_pkt_hdr {int /*<<< orphan*/  pkt_type; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t IFACEQ_CMD_IDX ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  venus_is_valid_state (struct venus_hfi_device*) ; 
 int /*<<< orphan*/  venus_soft_int (struct venus_hfi_device*) ; 
 int venus_write_queue (struct venus_hfi_device*,struct iface_queue*,void*,scalar_t__*) ; 

__attribute__((used)) static int venus_iface_cmdq_write_nolock(struct venus_hfi_device *hdev,
					 void *pkt)
{
	struct device *dev = hdev->core->dev;
	struct hfi_pkt_hdr *cmd_packet;
	struct iface_queue *queue;
	u32 rx_req;
	int ret;

	if (!venus_is_valid_state(hdev))
		return -EINVAL;

	cmd_packet = (struct hfi_pkt_hdr *)pkt;
	hdev->last_packet_type = cmd_packet->pkt_type;

	queue = &hdev->queues[IFACEQ_CMD_IDX];

	ret = venus_write_queue(hdev, queue, pkt, &rx_req);
	if (ret) {
		dev_err(dev, "write to iface cmd queue failed (%d)\n", ret);
		return ret;
	}

	if (rx_req)
		venus_soft_int(hdev);

	return 0;
}