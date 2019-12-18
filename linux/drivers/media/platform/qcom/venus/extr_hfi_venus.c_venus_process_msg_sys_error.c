#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct venus_hfi_device {int dummy; } ;
struct hfi_msg_event_notify_pkt {scalar_t__ event_id; } ;

/* Variables and functions */
 scalar_t__ HFI_EVENT_SYS_ERROR ; 
 int /*<<< orphan*/  VENUS_STATE_DEINIT ; 
 int /*<<< orphan*/  venus_halt_axi (struct venus_hfi_device*) ; 
 int /*<<< orphan*/  venus_set_state (struct venus_hfi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  venus_sfr_print (struct venus_hfi_device*) ; 

__attribute__((used)) static void venus_process_msg_sys_error(struct venus_hfi_device *hdev,
					void *packet)
{
	struct hfi_msg_event_notify_pkt *event_pkt = packet;

	if (event_pkt->event_id != HFI_EVENT_SYS_ERROR)
		return;

	venus_set_state(hdev, VENUS_STATE_DEINIT);

	/*
	 * Once SYS_ERROR received from HW, it is safe to halt the AXI.
	 * With SYS_ERROR, Venus FW may have crashed and HW might be
	 * active and causing unnecessary transactions. Hence it is
	 * safe to stop all AXI transactions from venus subsystem.
	 */
	venus_halt_axi(hdev);
	venus_sfr_print(hdev);
}