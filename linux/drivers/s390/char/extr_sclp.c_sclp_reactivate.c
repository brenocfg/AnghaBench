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

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ sclp_activation_state ; 
 scalar_t__ sclp_activation_state_activating ; 
 scalar_t__ sclp_activation_state_active ; 
 scalar_t__ sclp_activation_state_inactive ; 
 int sclp_init_mask (int) ; 
 int /*<<< orphan*/  sclp_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
sclp_reactivate(void)
{
	unsigned long flags;
	int rc;

	spin_lock_irqsave(&sclp_lock, flags);
	/* Reactivate can only be called when inactive */
	if (sclp_activation_state != sclp_activation_state_inactive) {
		spin_unlock_irqrestore(&sclp_lock, flags);
		return -EINVAL;
	}
	sclp_activation_state = sclp_activation_state_activating;
	spin_unlock_irqrestore(&sclp_lock, flags);
	rc = sclp_init_mask(1);
	spin_lock_irqsave(&sclp_lock, flags);
	if (rc == 0)
		sclp_activation_state = sclp_activation_state_active;
	else
		sclp_activation_state = sclp_activation_state_inactive;
	spin_unlock_irqrestore(&sclp_lock, flags);
	return rc;
}