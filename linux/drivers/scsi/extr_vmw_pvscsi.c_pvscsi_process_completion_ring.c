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
struct pvscsi_adapter {struct PVSCSIRingCmpDesc* cmp_ring; struct PVSCSIRingsState* rings_state; } ;
struct PVSCSIRingsState {int cmpConsIdx; int cmpProdIdx; int /*<<< orphan*/  cmpNumEntriesLog2; } ;
struct PVSCSIRingCmpDesc {int dummy; } ;

/* Variables and functions */
 int MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  pvscsi_complete_request (struct pvscsi_adapter*,struct PVSCSIRingCmpDesc*) ; 

__attribute__((used)) static void pvscsi_process_completion_ring(struct pvscsi_adapter *adapter)
{
	struct PVSCSIRingsState *s = adapter->rings_state;
	struct PVSCSIRingCmpDesc *ring = adapter->cmp_ring;
	u32 cmp_entries = s->cmpNumEntriesLog2;

	while (s->cmpConsIdx != s->cmpProdIdx) {
		struct PVSCSIRingCmpDesc *e = ring + (s->cmpConsIdx &
						      MASK(cmp_entries));
		/*
		 * This barrier() ensures that *e is not dereferenced while
		 * the device emulation still writes data into the slot.
		 * Since the device emulation advances s->cmpProdIdx only after
		 * updating the slot we want to check it first.
		 */
		barrier();
		pvscsi_complete_request(adapter, e);
		/*
		 * This barrier() ensures that compiler doesn't reorder write
		 * to s->cmpConsIdx before the read of (*e) inside
		 * pvscsi_complete_request. Otherwise, device emulation may
		 * overwrite *e before we had a chance to read it.
		 */
		barrier();
		s->cmpConsIdx++;
	}
}