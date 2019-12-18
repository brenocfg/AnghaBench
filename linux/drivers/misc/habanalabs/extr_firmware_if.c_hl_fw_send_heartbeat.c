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
typedef  int /*<<< orphan*/  u32 ;
struct hl_device {TYPE_1__* asic_funcs; } ;
struct armcp_packet {int /*<<< orphan*/  value; int /*<<< orphan*/  ctl; } ;
typedef  int /*<<< orphan*/  hb_pkt ;
struct TYPE_2__ {int (* send_cpu_message ) (struct hl_device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,long*) ;} ;

/* Variables and functions */
 long ARMCP_PACKET_FENCE_VAL ; 
 int ARMCP_PACKET_TEST ; 
 int ARMCP_PKT_CTL_OPCODE_SHIFT ; 
 int EIO ; 
 int /*<<< orphan*/  HL_DEVICE_TIMEOUT_USEC ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (long) ; 
 int stub1 (struct hl_device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,long*) ; 

int hl_fw_send_heartbeat(struct hl_device *hdev)
{
	struct armcp_packet hb_pkt = {};
	long result;
	int rc;

	hb_pkt.ctl = cpu_to_le32(ARMCP_PACKET_TEST <<
					ARMCP_PKT_CTL_OPCODE_SHIFT);
	hb_pkt.value = cpu_to_le64(ARMCP_PACKET_FENCE_VAL);

	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &hb_pkt,
			sizeof(hb_pkt), HL_DEVICE_TIMEOUT_USEC, &result);

	if ((rc) || (result != ARMCP_PACKET_FENCE_VAL))
		rc = -EIO;

	return rc;
}