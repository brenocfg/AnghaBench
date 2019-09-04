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
struct fw_ohci {int pri_req_max; int /*<<< orphan*/  lock; int /*<<< orphan*/  csr_state_setclear_abdicate; int /*<<< orphan*/  is_root; } ;
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
 int /*<<< orphan*/  OHCI1394_LinkControlSet ; 
 int OHCI1394_LinkControl_cycleMaster ; 
 int /*<<< orphan*/  OHCI1394_NodeID ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct fw_ohci* fw_ohci (struct fw_card*) ; 
 int get_cycle_time (struct fw_ohci*) ; 
 int reg_read (struct fw_ohci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int update_bus_time (struct fw_ohci*) ; 

__attribute__((used)) static u32 ohci_read_csr(struct fw_card *card, int csr_offset)
{
	struct fw_ohci *ohci = fw_ohci(card);
	unsigned long flags;
	u32 value;

	switch (csr_offset) {
	case CSR_STATE_CLEAR:
	case CSR_STATE_SET:
		if (ohci->is_root &&
		    (reg_read(ohci, OHCI1394_LinkControlSet) &
		     OHCI1394_LinkControl_cycleMaster))
			value = CSR_STATE_BIT_CMSTR;
		else
			value = 0;
		if (ohci->csr_state_setclear_abdicate)
			value |= CSR_STATE_BIT_ABDICATE;

		return value;

	case CSR_NODE_IDS:
		return reg_read(ohci, OHCI1394_NodeID) << 16;

	case CSR_CYCLE_TIME:
		return get_cycle_time(ohci);

	case CSR_BUS_TIME:
		/*
		 * We might be called just after the cycle timer has wrapped
		 * around but just before the cycle64Seconds handler, so we
		 * better check here, too, if the bus time needs to be updated.
		 */
		spin_lock_irqsave(&ohci->lock, flags);
		value = update_bus_time(ohci);
		spin_unlock_irqrestore(&ohci->lock, flags);
		return value;

	case CSR_BUSY_TIMEOUT:
		value = reg_read(ohci, OHCI1394_ATRetries);
		return (value >> 4) & 0x0ffff00f;

	case CSR_PRIORITY_BUDGET:
		return (reg_read(ohci, OHCI1394_FairnessControl) & 0x3f) |
			(ohci->pri_req_max << 8);

	default:
		WARN_ON(1);
		return 0;
	}
}