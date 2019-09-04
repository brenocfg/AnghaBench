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
struct venus_resources {int /*<<< orphan*/  vmem_addr; int /*<<< orphan*/  vmem_size; int /*<<< orphan*/  vmem_id; } ;
struct venus_hfi_device {int irq_status; int /*<<< orphan*/  pwr_collapse_prep; int /*<<< orphan*/  release_resource; void* pkt_buf; TYPE_1__* core; } ;
struct venus_core {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {struct venus_resources* res; } ;

/* Variables and functions */
#define  HFI_MSG_EVENT_NOTIFY 131 
#define  HFI_MSG_SYS_INIT 130 
#define  HFI_MSG_SYS_PC_PREP 129 
#define  HFI_MSG_SYS_RELEASE_RESOURCE 128 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int WRAPPER_INTR_STATUS_A2HWD_MASK ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int hfi_process_msg_packet (struct venus_core*,void*) ; 
 int /*<<< orphan*/  hfi_process_watchdog_timeout (struct venus_core*) ; 
 struct venus_hfi_device* to_hfi_priv (struct venus_core*) ; 
 int /*<<< orphan*/  venus_flush_debug_queue (struct venus_hfi_device*) ; 
 int /*<<< orphan*/  venus_hfi_core_set_resource (struct venus_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct venus_hfi_device*) ; 
 int /*<<< orphan*/  venus_iface_msgq_read (struct venus_hfi_device*,void*) ; 
 int /*<<< orphan*/  venus_process_msg_sys_error (struct venus_hfi_device*,void*) ; 
 int /*<<< orphan*/  venus_sfr_print (struct venus_hfi_device*) ; 

__attribute__((used)) static irqreturn_t venus_isr_thread(struct venus_core *core)
{
	struct venus_hfi_device *hdev = to_hfi_priv(core);
	const struct venus_resources *res;
	void *pkt;
	u32 msg_ret;

	if (!hdev)
		return IRQ_NONE;

	res = hdev->core->res;
	pkt = hdev->pkt_buf;

	if (hdev->irq_status & WRAPPER_INTR_STATUS_A2HWD_MASK) {
		venus_sfr_print(hdev);
		hfi_process_watchdog_timeout(core);
	}

	while (!venus_iface_msgq_read(hdev, pkt)) {
		msg_ret = hfi_process_msg_packet(core, pkt);
		switch (msg_ret) {
		case HFI_MSG_EVENT_NOTIFY:
			venus_process_msg_sys_error(hdev, pkt);
			break;
		case HFI_MSG_SYS_INIT:
			venus_hfi_core_set_resource(core, res->vmem_id,
						    res->vmem_size,
						    res->vmem_addr,
						    hdev);
			break;
		case HFI_MSG_SYS_RELEASE_RESOURCE:
			complete(&hdev->release_resource);
			break;
		case HFI_MSG_SYS_PC_PREP:
			complete(&hdev->pwr_collapse_prep);
			break;
		default:
			break;
		}
	}

	venus_flush_debug_queue(hdev);

	return IRQ_HANDLED;
}