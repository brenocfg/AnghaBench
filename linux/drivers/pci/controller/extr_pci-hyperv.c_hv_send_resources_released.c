#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  slot; } ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
struct pci_child_message {TYPE_2__ wslot; TYPE_1__ message_type; } ;
struct hv_pcibus_device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  slot; } ;
struct TYPE_8__ {TYPE_3__ win_slot; } ;
struct hv_pci_dev {TYPE_4__ desc; } ;
struct hv_device {int /*<<< orphan*/  channel; } ;
typedef  int /*<<< orphan*/  pkt ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_RESOURCES_RELEASED ; 
 int /*<<< orphan*/  VM_PKT_DATA_INBAND ; 
 struct hv_pci_dev* get_pcichild_wslot (struct hv_pcibus_device*,int) ; 
 struct hv_pcibus_device* hv_get_drvdata (struct hv_device*) ; 
 int /*<<< orphan*/  memset (struct pci_child_message*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_pcichild (struct hv_pci_dev*) ; 
 int vmbus_sendpacket (int /*<<< orphan*/ ,struct pci_child_message*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hv_send_resources_released(struct hv_device *hdev)
{
	struct hv_pcibus_device *hbus = hv_get_drvdata(hdev);
	struct pci_child_message pkt;
	struct hv_pci_dev *hpdev;
	u32 wslot;
	int ret;

	for (wslot = 0; wslot < 256; wslot++) {
		hpdev = get_pcichild_wslot(hbus, wslot);
		if (!hpdev)
			continue;

		memset(&pkt, 0, sizeof(pkt));
		pkt.message_type.type = PCI_RESOURCES_RELEASED;
		pkt.wslot.slot = hpdev->desc.win_slot.slot;

		put_pcichild(hpdev);

		ret = vmbus_sendpacket(hdev->channel, &pkt, sizeof(pkt), 0,
				       VM_PKT_DATA_INBAND, 0);
		if (ret)
			return ret;
	}

	return 0;
}