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
typedef  long u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct hl_device {int /*<<< orphan*/  dev; TYPE_1__* asic_funcs; } ;
struct armcp_packet {int /*<<< orphan*/  ctl; } ;
typedef  int /*<<< orphan*/  pkt ;
struct TYPE_2__ {int (* send_cpu_message ) (struct hl_device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,long*) ;} ;

/* Variables and functions */
 int ARMCP_PACKET_MAX_POWER_GET ; 
 int ARMCP_PKT_CTL_OPCODE_SHIFT ; 
 int /*<<< orphan*/  SET_PWR_PKT_TIMEOUT ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (struct armcp_packet*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct hl_device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,long*) ; 

u64 hl_get_max_power(struct hl_device *hdev)
{
	struct armcp_packet pkt;
	long result;
	int rc;

	memset(&pkt, 0, sizeof(pkt));

	pkt.ctl = cpu_to_le32(ARMCP_PACKET_MAX_POWER_GET <<
				ARMCP_PKT_CTL_OPCODE_SHIFT);

	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, sizeof(pkt),
						SET_PWR_PKT_TIMEOUT, &result);

	if (rc) {
		dev_err(hdev->dev, "Failed to get max power, error %d\n", rc);
		result = rc;
	}

	return result;
}