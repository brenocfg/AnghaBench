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
struct ath6kl_device {int /*<<< orphan*/  ar; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath6kl_hif_disable_intrs (struct ath6kl_device*) ; 
 int ath6kl_hif_enable_intrs (struct ath6kl_device*) ; 
 int /*<<< orphan*/  ath6kl_hif_irq_enable (int /*<<< orphan*/ ) ; 

int ath6kl_hif_unmask_intrs(struct ath6kl_device *dev)
{
	int status = 0;

	/*
	 * Make sure interrupt are disabled before unmasking at the HIF
	 * layer. The rationale here is that between device insertion
	 * (where we clear the interrupts the first time) and when HTC
	 * is finally ready to handle interrupts, other software can perform
	 * target "soft" resets. The ATH6KL interrupt enables reset back to an
	 * "enabled" state when this happens.
	 */
	ath6kl_hif_disable_intrs(dev);

	/* unmask the host controller interrupts */
	ath6kl_hif_irq_enable(dev->ar);
	status = ath6kl_hif_enable_intrs(dev);

	return status;
}