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
typedef  int /*<<< orphan*/  u32 ;
struct pvscsi_adapter {struct PVSCSIRingMsgDesc* msg_ring; struct PVSCSIRingsState* rings_state; } ;
struct PVSCSIRingsState {int msgConsIdx; int /*<<< orphan*/  msgNumEntriesLog2; } ;
struct PVSCSIRingMsgDesc {int dummy; } ;

/* Variables and functions */
 int MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  barrier () ; 
 scalar_t__ pvscsi_msg_pending (struct pvscsi_adapter const*) ; 
 int /*<<< orphan*/  pvscsi_process_msg (struct pvscsi_adapter const*,struct PVSCSIRingMsgDesc*) ; 

__attribute__((used)) static void pvscsi_process_msg_ring(const struct pvscsi_adapter *adapter)
{
	struct PVSCSIRingsState *s = adapter->rings_state;
	struct PVSCSIRingMsgDesc *ring = adapter->msg_ring;
	u32 msg_entries = s->msgNumEntriesLog2;

	while (pvscsi_msg_pending(adapter)) {
		struct PVSCSIRingMsgDesc *e = ring + (s->msgConsIdx &
						      MASK(msg_entries));

		barrier();
		pvscsi_process_msg(adapter, e);
		barrier();
		s->msgConsIdx++;
	}
}