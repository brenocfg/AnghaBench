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
 int ath6kl_hif_disable_intrs (struct ath6kl_device*) ; 
 int /*<<< orphan*/  ath6kl_hif_irq_disable (int /*<<< orphan*/ ) ; 

int ath6kl_hif_mask_intrs(struct ath6kl_device *dev)
{
	/*
	 * Mask the interrupt at the HIF layer to avoid any stray interrupt
	 * taken while we zero out our shadow registers in
	 * ath6kl_hif_disable_intrs().
	 */
	ath6kl_hif_irq_disable(dev->ar);

	return ath6kl_hif_disable_intrs(dev);
}