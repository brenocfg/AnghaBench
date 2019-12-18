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
typedef  int /*<<< orphan*/  u32 ;
struct vmci_handle {int dummy; } ;
struct TYPE_2__ {scalar_t__ payload_size; int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct vmci_doorbell_notify_msg {TYPE_1__ hdr; struct vmci_handle handle; } ;
typedef  int /*<<< orphan*/  notify_msg ;

/* Variables and functions */
 int /*<<< orphan*/  VMCI_ANON_SRC_HANDLE ; 
 scalar_t__ VMCI_DG_HEADERSIZE ; 
 int /*<<< orphan*/  VMCI_DOORBELL_NOTIFY ; 
 int /*<<< orphan*/  VMCI_HYPERVISOR_CONTEXT_ID ; 
 int /*<<< orphan*/  vmci_make_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vmci_send_datagram (TYPE_1__*) ; 

__attribute__((used)) static int dbell_notify_as_guest(struct vmci_handle handle, u32 priv_flags)
{
	struct vmci_doorbell_notify_msg notify_msg;

	notify_msg.hdr.dst = vmci_make_handle(VMCI_HYPERVISOR_CONTEXT_ID,
					      VMCI_DOORBELL_NOTIFY);
	notify_msg.hdr.src = VMCI_ANON_SRC_HANDLE;
	notify_msg.hdr.payload_size = sizeof(notify_msg) - VMCI_DG_HEADERSIZE;
	notify_msg.handle = handle;

	return vmci_send_datagram(&notify_msg.hdr);
}