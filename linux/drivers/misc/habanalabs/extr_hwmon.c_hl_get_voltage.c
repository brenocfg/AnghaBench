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
struct hl_device {int /*<<< orphan*/  dev; TYPE_1__* asic_funcs; } ;
struct armcp_packet {void* type; void* sensor_index; int /*<<< orphan*/  ctl; } ;
typedef  int /*<<< orphan*/  pkt ;
struct TYPE_2__ {int (* send_cpu_message ) (struct hl_device*,int*,int,int /*<<< orphan*/ ,long*) ;} ;

/* Variables and functions */
 int ARMCP_PACKET_VOLTAGE_GET ; 
 int ARMCP_PKT_CTL_OPCODE_SHIFT ; 
 int /*<<< orphan*/  SENSORS_PKT_TIMEOUT ; 
 void* __cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  memset (struct armcp_packet*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct hl_device*,int*,int,int /*<<< orphan*/ ,long*) ; 

long hl_get_voltage(struct hl_device *hdev, int sensor_index, u32 attr)
{
	struct armcp_packet pkt;
	long result;
	int rc;

	memset(&pkt, 0, sizeof(pkt));

	pkt.ctl = cpu_to_le32(ARMCP_PACKET_VOLTAGE_GET <<
				ARMCP_PKT_CTL_OPCODE_SHIFT);
	pkt.sensor_index = __cpu_to_le16(sensor_index);
	pkt.type = __cpu_to_le16(attr);

	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, sizeof(pkt),
					SENSORS_PKT_TIMEOUT, &result);

	if (rc) {
		dev_err(hdev->dev,
			"Failed to get voltage from sensor %d, error %d\n",
			sensor_index, rc);
		result = 0;
	}

	return result;
}