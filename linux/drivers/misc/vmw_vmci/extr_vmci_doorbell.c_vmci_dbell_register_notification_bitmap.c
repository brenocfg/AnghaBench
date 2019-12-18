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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ payload_size; int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct vmci_notify_bm_set_msg {TYPE_1__ hdr; scalar_t__ bitmap_ppn32; scalar_t__ bitmap_ppn64; } ;
typedef  int /*<<< orphan*/  bitmap_set_msg ;

/* Variables and functions */
 int /*<<< orphan*/  VMCI_ANON_SRC_HANDLE ; 
 scalar_t__ VMCI_DG_HEADERSIZE ; 
 int /*<<< orphan*/  VMCI_HYPERVISOR_CONTEXT_ID ; 
 int /*<<< orphan*/  VMCI_SET_NOTIFY_BITMAP ; 
 int VMCI_SUCCESS ; 
 int /*<<< orphan*/  pr_devel (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  vmci_make_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vmci_send_datagram (TYPE_1__*) ; 
 scalar_t__ vmci_use_ppn64 () ; 

bool vmci_dbell_register_notification_bitmap(u64 bitmap_ppn)
{
	int result;
	struct vmci_notify_bm_set_msg bitmap_set_msg;

	bitmap_set_msg.hdr.dst = vmci_make_handle(VMCI_HYPERVISOR_CONTEXT_ID,
						  VMCI_SET_NOTIFY_BITMAP);
	bitmap_set_msg.hdr.src = VMCI_ANON_SRC_HANDLE;
	bitmap_set_msg.hdr.payload_size = sizeof(bitmap_set_msg) -
	    VMCI_DG_HEADERSIZE;
	if (vmci_use_ppn64())
		bitmap_set_msg.bitmap_ppn64 = bitmap_ppn;
	else
		bitmap_set_msg.bitmap_ppn32 = (u32) bitmap_ppn;

	result = vmci_send_datagram(&bitmap_set_msg.hdr);
	if (result != VMCI_SUCCESS) {
		pr_devel("Failed to register (PPN=%llu) as notification bitmap (error=%d)\n",
			 bitmap_ppn, result);
		return false;
	}
	return true;
}