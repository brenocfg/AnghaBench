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
 scalar_t__ sclp_activation_state_active ; 
 scalar_t__ sclp_activation_state_deactivating ; 
 scalar_t__ sclp_activation_state_inactive ; 
 int sclp_init_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sclp_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
sclp_deactivate(void)
{
	unsigned long flags;
	int rc;

	spin_lock_irqsave(&sclp_lock, flags);
	/* Deactivate can only be called when active */
	if (sclp_activation_state != sclp_activation_state_active) {
		spin_unlock_irqrestore(&sclp_lock, flags);
		return -EINVAL;
	}
	sclp_activation_state = sclp_activation_state_deactivating;
	spin_unlock_irqrestore(&sclp_lock, flags);
	rc = sclp_init_mask(0);
	spin_lock_irqsave(&sclp_lock, flags);
	if (rc == 0)
		sclp_activation_state = sclp_activation_state_inactive;
	else
		sclp_activation_state = sclp_activation_state_active;
	spin_unlock_irqrestore(&sclp_lock, flags);
	return rc;
}