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
struct hl_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {void* ctl; } ;
struct armcp_unmask_irq_arr_packet {TYPE_1__ armcp_pkt; int /*<<< orphan*/  irqs; void* length; } ;
typedef  int /*<<< orphan*/  irq_arr ;
typedef  void* __le32 ;

/* Variables and functions */
 int ARMCP_PACKET_UNMASK_RAZWI_IRQ_ARRAY ; 
 int ARMCP_PKT_CTL_OPCODE_SHIFT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HL_DEVICE_TIMEOUT_USEC ; 
 size_t USHRT_MAX ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int goya_send_cpu_message (struct hl_device*,int*,size_t,int /*<<< orphan*/ ,long*) ; 
 int /*<<< orphan*/  kfree (struct armcp_unmask_irq_arr_packet*) ; 
 struct armcp_unmask_irq_arr_packet* kzalloc (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int goya_unmask_irq_arr(struct hl_device *hdev, u32 *irq_arr,
		size_t irq_arr_size)
{
	struct armcp_unmask_irq_arr_packet *pkt;
	size_t total_pkt_size;
	long result;
	int rc;
	int irq_num_entries, irq_arr_index;
	__le32 *goya_irq_arr;

	total_pkt_size = sizeof(struct armcp_unmask_irq_arr_packet) +
			irq_arr_size;

	/* data should be aligned to 8 bytes in order to ArmCP to copy it */
	total_pkt_size = (total_pkt_size + 0x7) & ~0x7;

	/* total_pkt_size is casted to u16 later on */
	if (total_pkt_size > USHRT_MAX) {
		dev_err(hdev->dev, "too many elements in IRQ array\n");
		return -EINVAL;
	}

	pkt = kzalloc(total_pkt_size, GFP_KERNEL);
	if (!pkt)
		return -ENOMEM;

	irq_num_entries = irq_arr_size / sizeof(irq_arr[0]);
	pkt->length = cpu_to_le32(irq_num_entries);

	/* We must perform any necessary endianness conversation on the irq
	 * array being passed to the goya hardware
	 */
	for (irq_arr_index = 0, goya_irq_arr = (__le32 *) &pkt->irqs;
			irq_arr_index < irq_num_entries ; irq_arr_index++)
		goya_irq_arr[irq_arr_index] =
				cpu_to_le32(irq_arr[irq_arr_index]);

	pkt->armcp_pkt.ctl = cpu_to_le32(ARMCP_PACKET_UNMASK_RAZWI_IRQ_ARRAY <<
						ARMCP_PKT_CTL_OPCODE_SHIFT);

	rc = goya_send_cpu_message(hdev, (u32 *) pkt, total_pkt_size,
			HL_DEVICE_TIMEOUT_USEC, &result);

	if (rc)
		dev_err(hdev->dev, "failed to unmask IRQ array\n");

	kfree(pkt);

	return rc;
}