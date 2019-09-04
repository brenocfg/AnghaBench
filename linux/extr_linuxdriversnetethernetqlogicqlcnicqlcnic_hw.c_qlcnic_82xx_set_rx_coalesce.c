#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct qlcnic_nic_req {void** words; void* req_hdr; void* qhdr; } ;
struct qlcnic_adapter {TYPE_3__* netdev; TYPE_2__* ahw; scalar_t__ portnum; } ;
struct cmd_desc_type0 {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int rx_packets; int timer_out; scalar_t__ sts_ring_mask; scalar_t__ type; scalar_t__ rx_time_us; scalar_t__ flag; } ;
struct TYPE_5__ {TYPE_1__ coal; } ;

/* Variables and functions */
 int QLCNIC_CONFIG_INTR_COALESCE ; 
 int QLCNIC_HOST_REQUEST ; 
 void* cpu_to_le64 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memset (struct qlcnic_nic_req*,int /*<<< orphan*/ ,int) ; 
 int qlcnic_send_cmd_descs (struct qlcnic_adapter*,struct cmd_desc_type0*,int) ; 

int qlcnic_82xx_set_rx_coalesce(struct qlcnic_adapter *adapter)
{
	struct qlcnic_nic_req req;
	int rv;

	memset(&req, 0, sizeof(struct qlcnic_nic_req));

	req.qhdr = cpu_to_le64(QLCNIC_HOST_REQUEST << 23);

	req.req_hdr = cpu_to_le64(QLCNIC_CONFIG_INTR_COALESCE |
		((u64) adapter->portnum << 16));

	req.words[0] = cpu_to_le64(((u64) adapter->ahw->coal.flag) << 32);
	req.words[2] = cpu_to_le64(adapter->ahw->coal.rx_packets |
			((u64) adapter->ahw->coal.rx_time_us) << 16);
	req.words[5] = cpu_to_le64(adapter->ahw->coal.timer_out |
			((u64) adapter->ahw->coal.type) << 32 |
			((u64) adapter->ahw->coal.sts_ring_mask) << 40);
	rv = qlcnic_send_cmd_descs(adapter, (struct cmd_desc_type0 *)&req, 1);
	if (rv != 0)
		dev_err(&adapter->netdev->dev,
			"Could not send interrupt coalescing parameters\n");

	return rv;
}