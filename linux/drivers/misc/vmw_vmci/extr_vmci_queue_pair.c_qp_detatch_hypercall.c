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
struct TYPE_2__ {int payload_size; int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct vmci_handle {int dummy; } ;
struct vmci_qp_detach_msg {TYPE_1__ hdr; struct vmci_handle handle; } ;
typedef  int /*<<< orphan*/  handle ;

/* Variables and functions */
 int /*<<< orphan*/  VMCI_ANON_SRC_HANDLE ; 
 int /*<<< orphan*/  VMCI_HYPERVISOR_CONTEXT_ID ; 
 int /*<<< orphan*/  VMCI_QUEUEPAIR_DETACH ; 
 int /*<<< orphan*/  vmci_make_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vmci_send_datagram (TYPE_1__*) ; 

__attribute__((used)) static int qp_detatch_hypercall(struct vmci_handle handle)
{
	struct vmci_qp_detach_msg detach_msg;

	detach_msg.hdr.dst = vmci_make_handle(VMCI_HYPERVISOR_CONTEXT_ID,
					      VMCI_QUEUEPAIR_DETACH);
	detach_msg.hdr.src = VMCI_ANON_SRC_HANDLE;
	detach_msg.hdr.payload_size = sizeof(handle);
	detach_msg.handle = handle;

	return vmci_send_datagram(&detach_msg.hdr);
}