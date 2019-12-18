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
struct hl_device {TYPE_1__* asic_funcs; } ;
struct armcp_packet {int /*<<< orphan*/  ctl; } ;
typedef  int /*<<< orphan*/  pkt ;
struct TYPE_2__ {int (* send_cpu_message ) (struct hl_device*,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int ARMCP_PKT_CTL_OPCODE_SHIFT ; 
 int /*<<< orphan*/  HL_DEVICE_TIMEOUT_USEC ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int stub1 (struct hl_device*,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int hl_fw_send_pci_access_msg(struct hl_device *hdev, u32 opcode)
{
	struct armcp_packet pkt = {};

	pkt.ctl = cpu_to_le32(opcode << ARMCP_PKT_CTL_OPCODE_SHIFT);

	return hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt,
				sizeof(pkt), HL_DEVICE_TIMEOUT_USEC, NULL);
}