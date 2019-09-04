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
struct vmci_datagram {scalar_t__ payload_size; int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMCI_ANON_SRC_HANDLE ; 
 int /*<<< orphan*/  VMCI_GET_CONTEXT_ID ; 
 int /*<<< orphan*/  VMCI_HYPERVISOR_CONTEXT_ID ; 
 scalar_t__ VMCI_INVALID_ID ; 
 scalar_t__ vm_context_id ; 
 int /*<<< orphan*/  vmci_make_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vmci_send_datagram (struct vmci_datagram*) ; 

u32 vmci_get_vm_context_id(void)
{
	if (vm_context_id == VMCI_INVALID_ID) {
		struct vmci_datagram get_cid_msg;
		get_cid_msg.dst =
		    vmci_make_handle(VMCI_HYPERVISOR_CONTEXT_ID,
				     VMCI_GET_CONTEXT_ID);
		get_cid_msg.src = VMCI_ANON_SRC_HANDLE;
		get_cid_msg.payload_size = 0;
		vm_context_id = vmci_send_datagram(&get_cid_msg);
	}
	return vm_context_id;
}