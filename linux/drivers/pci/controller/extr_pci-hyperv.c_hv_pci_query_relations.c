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
struct pci_message {int /*<<< orphan*/  type; } ;
struct hv_pcibus_device {int /*<<< orphan*/  survey_event; } ;
struct hv_device {int /*<<< orphan*/  channel; } ;
struct completion {int dummy; } ;
typedef  int /*<<< orphan*/  message ;

/* Variables and functions */
 int ENOTEMPTY ; 
 int /*<<< orphan*/  PCI_QUERY_BUS_RELATIONS ; 
 int /*<<< orphan*/  VM_PKT_DATA_INBAND ; 
 scalar_t__ cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct completion*) ; 
 struct hv_pcibus_device* hv_get_drvdata (struct hv_device*) ; 
 int /*<<< orphan*/  init_completion (struct completion*) ; 
 int /*<<< orphan*/  memset (struct pci_message*,int /*<<< orphan*/ ,int) ; 
 int vmbus_sendpacket (int /*<<< orphan*/ ,struct pci_message*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wait_for_response (struct hv_device*,struct completion*) ; 

__attribute__((used)) static int hv_pci_query_relations(struct hv_device *hdev)
{
	struct hv_pcibus_device *hbus = hv_get_drvdata(hdev);
	struct pci_message message;
	struct completion comp;
	int ret;

	/* Ask the host to send along the list of child devices */
	init_completion(&comp);
	if (cmpxchg(&hbus->survey_event, NULL, &comp))
		return -ENOTEMPTY;

	memset(&message, 0, sizeof(message));
	message.type = PCI_QUERY_BUS_RELATIONS;

	ret = vmbus_sendpacket(hdev->channel, &message, sizeof(message),
			       0, VM_PKT_DATA_INBAND, 0);
	if (!ret)
		ret = wait_for_response(hdev, &comp);

	return ret;
}