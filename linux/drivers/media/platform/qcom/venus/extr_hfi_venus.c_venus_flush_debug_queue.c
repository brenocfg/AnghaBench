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
struct venus_hfi_device {void* dbg_buf; TYPE_1__* core; } ;
struct hfi_msg_sys_debug_pkt {int /*<<< orphan*/  msg_data; } ;
struct TYPE_4__ {scalar_t__ pkt_type; } ;
struct hfi_msg_sys_coverage_pkt {TYPE_2__ hdr; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device* dev; } ;

/* Variables and functions */
 scalar_t__ HFI_MSG_SYS_COV ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  venus_iface_dbgq_read (struct venus_hfi_device*,void*) ; 

__attribute__((used)) static void venus_flush_debug_queue(struct venus_hfi_device *hdev)
{
	struct device *dev = hdev->core->dev;
	void *packet = hdev->dbg_buf;

	while (!venus_iface_dbgq_read(hdev, packet)) {
		struct hfi_msg_sys_coverage_pkt *pkt = packet;

		if (pkt->hdr.pkt_type != HFI_MSG_SYS_COV) {
			struct hfi_msg_sys_debug_pkt *pkt = packet;

			dev_dbg(dev, "%s", pkt->msg_data);
		}
	}
}