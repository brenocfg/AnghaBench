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
struct dvb_ca_en50221 {scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  ci_present; } ;
struct budget_ci {int slot_status; TYPE_1__ budget; } ;

/* Variables and functions */
 unsigned int CICONTROL_CAMDETECT ; 
 int /*<<< orphan*/  DEBIADDR_CICONTROL ; 
 int /*<<< orphan*/  DEBICICTL ; 
 int DVB_CA_EN50221_POLL_CAM_PRESENT ; 
 int DVB_CA_EN50221_POLL_CAM_READY ; 
 int EINVAL ; 
 int SLOTSTATUS_NONE ; 
 int SLOTSTATUS_PRESENT ; 
 int SLOTSTATUS_READY ; 
 int SLOTSTATUS_RESET ; 
 int ciintf_read_attribute_mem (struct dvb_ca_en50221*,int,int /*<<< orphan*/ ) ; 
 unsigned int ttpci_budget_debiread (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ciintf_poll_slot_status(struct dvb_ca_en50221 *ca, int slot, int open)
{
	struct budget_ci *budget_ci = (struct budget_ci *) ca->data;
	unsigned int flags;

	// ensure we don't get spurious IRQs during initialisation
	if (!budget_ci->budget.ci_present)
		return -EINVAL;

	// read the CAM status
	flags = ttpci_budget_debiread(&budget_ci->budget, DEBICICTL, DEBIADDR_CICONTROL, 1, 1, 0);
	if (flags & CICONTROL_CAMDETECT) {
		// mark it as present if it wasn't before
		if (budget_ci->slot_status & SLOTSTATUS_NONE) {
			budget_ci->slot_status = SLOTSTATUS_PRESENT;
		}

		// during a RESET, we check if we can read from IO memory to see when CAM is ready
		if (budget_ci->slot_status & SLOTSTATUS_RESET) {
			if (ciintf_read_attribute_mem(ca, slot, 0) == 0x1d) {
				budget_ci->slot_status = SLOTSTATUS_READY;
			}
		}
	} else {
		budget_ci->slot_status = SLOTSTATUS_NONE;
	}

	if (budget_ci->slot_status != SLOTSTATUS_NONE) {
		if (budget_ci->slot_status & SLOTSTATUS_READY) {
			return DVB_CA_EN50221_POLL_CAM_PRESENT | DVB_CA_EN50221_POLL_CAM_READY;
		}
		return DVB_CA_EN50221_POLL_CAM_PRESENT;
	}

	return 0;
}