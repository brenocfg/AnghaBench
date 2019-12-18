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
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct pci_version_request {void* protocol_version; TYPE_1__ message_type; } ;
struct pci_packet {int /*<<< orphan*/  message; struct hv_pci_compl* compl_ctxt; int /*<<< orphan*/  completion_func; } ;
struct hv_pci_compl {int /*<<< orphan*/  host_event; int /*<<< orphan*/  completion_status; } ;
struct hv_device {int /*<<< orphan*/  device; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int ARRAY_SIZE (void**) ; 
 int ENOMEM ; 
 int EPROTO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PCI_QUERY_PROTOCOL_VERSION ; 
 int /*<<< orphan*/  STATUS_REVISION_MISMATCH ; 
 int /*<<< orphan*/  VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED ; 
 int /*<<< orphan*/  VM_PKT_DATA_INBAND ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,void*) ; 
 int /*<<< orphan*/  hv_pci_generic_compl ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct pci_packet*) ; 
 struct pci_packet* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* pci_protocol_version ; 
 void** pci_protocol_versions ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int vmbus_sendpacket (int /*<<< orphan*/ ,struct pci_version_request*,int,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wait_for_response (struct hv_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hv_pci_protocol_negotiation(struct hv_device *hdev)
{
	struct pci_version_request *version_req;
	struct hv_pci_compl comp_pkt;
	struct pci_packet *pkt;
	int ret;
	int i;

	/*
	 * Initiate the handshake with the host and negotiate
	 * a version that the host can support. We start with the
	 * highest version number and go down if the host cannot
	 * support it.
	 */
	pkt = kzalloc(sizeof(*pkt) + sizeof(*version_req), GFP_KERNEL);
	if (!pkt)
		return -ENOMEM;

	init_completion(&comp_pkt.host_event);
	pkt->completion_func = hv_pci_generic_compl;
	pkt->compl_ctxt = &comp_pkt;
	version_req = (struct pci_version_request *)&pkt->message;
	version_req->message_type.type = PCI_QUERY_PROTOCOL_VERSION;

	for (i = 0; i < ARRAY_SIZE(pci_protocol_versions); i++) {
		version_req->protocol_version = pci_protocol_versions[i];
		ret = vmbus_sendpacket(hdev->channel, version_req,
				sizeof(struct pci_version_request),
				(unsigned long)pkt, VM_PKT_DATA_INBAND,
				VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED);
		if (!ret)
			ret = wait_for_response(hdev, &comp_pkt.host_event);

		if (ret) {
			dev_err(&hdev->device,
				"PCI Pass-through VSP failed to request version: %d",
				ret);
			goto exit;
		}

		if (comp_pkt.completion_status >= 0) {
			pci_protocol_version = pci_protocol_versions[i];
			dev_info(&hdev->device,
				"PCI VMBus probing: Using version %#x\n",
				pci_protocol_version);
			goto exit;
		}

		if (comp_pkt.completion_status != STATUS_REVISION_MISMATCH) {
			dev_err(&hdev->device,
				"PCI Pass-through VSP failed version request: %#x",
				comp_pkt.completion_status);
			ret = -EPROTO;
			goto exit;
		}

		reinit_completion(&comp_pkt.host_event);
	}

	dev_err(&hdev->device,
		"PCI pass-through VSP failed to find supported version");
	ret = -EPROTO;

exit:
	kfree(pkt);
	return ret;
}