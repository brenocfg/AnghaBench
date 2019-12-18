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
struct controller {scalar_t__ state; int /*<<< orphan*/  reset_lock; int /*<<< orphan*/  state_lock; } ;

/* Variables and functions */
 scalar_t__ BLINKINGOFF_STATE ; 
 scalar_t__ BLINKINGON_STATE ; 
 scalar_t__ OFF_STATE ; 
 scalar_t__ ON_STATE ; 
 int /*<<< orphan*/  PCI_EXP_SLTSTA_PDC ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pciehp_card_present_or_link_active (struct controller*) ; 
 int /*<<< orphan*/  pciehp_request (struct controller*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pciehp_check_presence(struct controller *ctrl)
{
	bool occupied;

	down_read(&ctrl->reset_lock);
	mutex_lock(&ctrl->state_lock);

	occupied = pciehp_card_present_or_link_active(ctrl);
	if ((occupied && (ctrl->state == OFF_STATE ||
			  ctrl->state == BLINKINGON_STATE)) ||
	    (!occupied && (ctrl->state == ON_STATE ||
			   ctrl->state == BLINKINGOFF_STATE)))
		pciehp_request(ctrl, PCI_EXP_SLTSTA_PDC);

	mutex_unlock(&ctrl->state_lock);
	up_read(&ctrl->reset_lock);
}