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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct hl_device {int /*<<< orphan*/  dev; TYPE_1__* asic_funcs; } ;
struct armcp_packet {int /*<<< orphan*/  value; void* pll_index; void* ctl; } ;
typedef  int /*<<< orphan*/  pkt ;
struct TYPE_2__ {int (* send_cpu_message ) (struct hl_device*,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int ARMCP_PACKET_FREQUENCY_SET ; 
 int ARMCP_PKT_CTL_OPCODE_SHIFT ; 
 int /*<<< orphan*/  SET_CLK_PKT_TIMEOUT ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  memset (struct armcp_packet*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct hl_device*,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void hl_set_frequency(struct hl_device *hdev, u32 pll_index, u64 freq)
{
	struct armcp_packet pkt;
	int rc;

	memset(&pkt, 0, sizeof(pkt));

	pkt.ctl = cpu_to_le32(ARMCP_PACKET_FREQUENCY_SET <<
					ARMCP_PKT_CTL_OPCODE_SHIFT);
	pkt.pll_index = cpu_to_le32(pll_index);
	pkt.value = cpu_to_le64(freq);

	rc = hdev->asic_funcs->send_cpu_message(hdev, (u32 *) &pkt, sizeof(pkt),
					SET_CLK_PKT_TIMEOUT, NULL);

	if (rc)
		dev_err(hdev->dev,
			"Failed to set frequency to PLL %d, error %d\n",
			pll_index, rc);
}