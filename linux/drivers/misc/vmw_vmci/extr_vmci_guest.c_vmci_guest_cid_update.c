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
typedef  scalar_t__ u32 ;
struct vmci_event_payld_ctx {scalar_t__ context_id; } ;
struct vmci_event_data {int /*<<< orphan*/  event; } ;

/* Variables and functions */
 scalar_t__ VMCI_INVALID_ID ; 
 scalar_t__ ctx_update_sub_id ; 
 int /*<<< orphan*/  pr_devel (char*,...) ; 
 scalar_t__ vm_context_id ; 
 struct vmci_event_payld_ctx* vmci_event_data_const_payload (struct vmci_event_data const*) ; 

__attribute__((used)) static void vmci_guest_cid_update(u32 sub_id,
				  const struct vmci_event_data *event_data,
				  void *client_data)
{
	const struct vmci_event_payld_ctx *ev_payload =
				vmci_event_data_const_payload(event_data);

	if (sub_id != ctx_update_sub_id) {
		pr_devel("Invalid subscriber (ID=0x%x)\n", sub_id);
		return;
	}

	if (!event_data || ev_payload->context_id == VMCI_INVALID_ID) {
		pr_devel("Invalid event data\n");
		return;
	}

	pr_devel("Updating context from (ID=0x%x) to (ID=0x%x) on event (type=%d)\n",
		 vm_context_id, ev_payload->context_id, event_data->event);

	vm_context_id = ev_payload->context_id;
}