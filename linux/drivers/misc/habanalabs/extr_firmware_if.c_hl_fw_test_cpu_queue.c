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
typedef  int /*<<< orphan*/  test_pkt ;
struct hl_device {int /*<<< orphan*/  dev; TYPE_1__* asic_funcs; } ;
struct armcp_packet {int /*<<< orphan*/  value; int /*<<< orphan*/  ctl; } ;
struct TYPE_2__ {int (* send_cpu_message ) (struct hl_device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,long*) ;} ;

/* Variables and functions */
 long ARMCP_PACKET_FENCE_VAL ; 
 int ARMCP_PACKET_TEST ; 
 int ARMCP_PKT_CTL_OPCODE_SHIFT ; 
 int /*<<< orphan*/  HL_DEVICE_TIMEOUT_USEC ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (long) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int stub1 (struct hl_device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,long*) ; 

int hl_fw_test_cpu_queue(struct hl_device *hdev)
{
	struct armcp_packet test_pkt = {};
	long result;
	int rc;

	test_pkt.ctl = cpu_to_le32(ARMCP_PACKET_TEST <<
					ARMCP_PKT_CTL_OPCODE_SHIFT);
	test_pkt.value = cpu_to_le64(ARMCP_PACKET_FENCE_VAL);

	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &test_pkt,
			sizeof(test_pkt), HL_DEVICE_TIMEOUT_USEC, &result);

	if (!rc) {
		if (result == ARMCP_PACKET_FENCE_VAL)
			dev_info(hdev->dev,
				"queue test on CPU queue succeeded\n");
		else
			dev_err(hdev->dev,
				"CPU queue test failed (0x%08lX)\n", result);
	} else {
		dev_err(hdev->dev, "CPU queue test failed, error %d\n", rc);
	}

	return rc;
}