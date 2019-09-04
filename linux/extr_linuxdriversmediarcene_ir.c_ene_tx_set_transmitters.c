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
struct ene_device {int transmitter_mask; int /*<<< orphan*/  hw_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENE_GPIOFS1 ; 
 int /*<<< orphan*/  ENE_GPIOFS1_GPIO0D ; 
 int /*<<< orphan*/  ENE_GPIOFS8 ; 
 int /*<<< orphan*/  ENE_GPIOFS8_GPIO41 ; 
 int /*<<< orphan*/  ene_set_clear_reg_mask (struct ene_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ene_tx_set_transmitters(struct ene_device *dev)
{
	unsigned long flags;

	spin_lock_irqsave(&dev->hw_lock, flags);
	ene_set_clear_reg_mask(dev, ENE_GPIOFS8, ENE_GPIOFS8_GPIO41,
					!!(dev->transmitter_mask & 0x01));
	ene_set_clear_reg_mask(dev, ENE_GPIOFS1, ENE_GPIOFS1_GPIO0D,
					!!(dev->transmitter_mask & 0x02));
	spin_unlock_irqrestore(&dev->hw_lock, flags);
}