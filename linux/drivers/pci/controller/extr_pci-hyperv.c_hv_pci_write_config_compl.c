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
struct pci_response {int /*<<< orphan*/  status; } ;
struct hv_pci_compl {int /*<<< orphan*/  host_event; int /*<<< orphan*/  completion_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hv_pci_write_config_compl(void *context, struct pci_response *resp,
				      int resp_packet_size)
{
	struct hv_pci_compl *comp_pkt = context;

	comp_pkt->completion_status = resp->status;
	complete(&comp_pkt->host_event);
}