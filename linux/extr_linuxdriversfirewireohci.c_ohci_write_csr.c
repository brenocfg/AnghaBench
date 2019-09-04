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
typedef  int u32 ;
struct fw_ohci {int csr_state_setclear_abdicate; int bus_time; int /*<<< orphan*/  lock; int /*<<< orphan*/  is_root; } ;
struct fw_card {int dummy; } ;

/* Variables and functions */
#define  CSR_BUSY_TIMEOUT 134 
#define  CSR_BUS_TIME 133 
#define  CSR_CYCLE_TIME 132 
#define  CSR_NODE_IDS 131 
#define  CSR_PRIORITY_BUDGET 130 
 int CSR_STATE_BIT_ABDICATE ; 
 int CSR_STATE_BIT_CMSTR ; 
#define  CSR_STATE_CLEAR 129 
#define  CSR_STATE_SET 128 
 int /*<<< orphan*/  OHCI1394_ATRetries ; 
 int /*<<< orphan*/  OHCI1394_FairnessControl ; 
 int /*<<< orphan*/  OHCI1394_IntEventSet ; 
 int /*<<< orphan*/  OHCI1394_IsochronousCycleTimer ; 
 int /*<<< orphan*/  OHCI1394_LinkControlClear ; 
 int /*<<< orphan*/  OHCI1394_LinkControlSet ; 
 int OHCI1394_LinkControl_cycleMaster ; 
 int /*<<< orphan*/  OHCI1394_NodeID ; 
 int OHCI1394_cycleInconsistent ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  flush_writes (struct fw_ohci*) ; 
 struct fw_ohci* fw_ohci (struct fw_card*) ; 
 int /*<<< orphan*/  reg_write (struct fw_ohci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int update_bus_time (struct fw_ohci*) ; 

__attribute__((used)) static void ohci_write_csr(struct fw_card *card, int csr_offset, u32 value)
{
	struct fw_ohci *ohci = fw_ohci(card);
	unsigned long flags;

	switch (csr_offset) {
	case CSR_STATE_CLEAR:
		if ((value & CSR_STATE_BIT_CMSTR) && ohci->is_root) {
			reg_write(ohci, OHCI1394_LinkControlClear,
				  OHCI1394_LinkControl_cycleMaster);
			flush_writes(ohci);
		}
		if (value & CSR_STATE_BIT_ABDICATE)
			ohci->csr_state_setclear_abdicate = false;
		break;

	case CSR_STATE_SET:
		if ((value & CSR_STATE_BIT_CMSTR) && ohci->is_root) {
			reg_write(ohci, OHCI1394_LinkControlSet,
				  OHCI1394_LinkControl_cycleMaster);
			flush_writes(ohci);
		}
		if (value & CSR_STATE_BIT_ABDICATE)
			ohci->csr_state_setclear_abdicate = true;
		break;

	case CSR_NODE_IDS:
		reg_write(ohci, OHCI1394_NodeID, value >> 16);
		flush_writes(ohci);
		break;

	case CSR_CYCLE_TIME:
		reg_write(ohci, OHCI1394_IsochronousCycleTimer, value);
		reg_write(ohci, OHCI1394_IntEventSet,
			  OHCI1394_cycleInconsistent);
		flush_writes(ohci);
		break;

	case CSR_BUS_TIME:
		spin_lock_irqsave(&ohci->lock, flags);
		ohci->bus_time = (update_bus_time(ohci) & 0x40) |
		                 (value & ~0x7f);
		spin_unlock_irqrestore(&ohci->lock, flags);
		break;

	case CSR_BUSY_TIMEOUT:
		value = (value & 0xf) | ((value & 0xf) << 4) |
			((value & 0xf) << 8) | ((value & 0x0ffff000) << 4);
		reg_write(ohci, OHCI1394_ATRetries, value);
		flush_writes(ohci);
		break;

	case CSR_PRIORITY_BUDGET:
		reg_write(ohci, OHCI1394_FairnessControl, value & 0x3f);
		flush_writes(ohci);
		break;

	default:
		WARN_ON(1);
		break;
	}
}