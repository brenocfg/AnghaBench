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
typedef  int uint8_t ;
struct r852_device {int card_detected; int /*<<< orphan*/  irqlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  R852_CARD_STA ; 
 int R852_CARD_STA_PRESENT ; 
 int r852_read_reg (struct r852_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void r852_card_update_present(struct r852_device *dev)
{
	unsigned long flags;
	uint8_t reg;

	spin_lock_irqsave(&dev->irqlock, flags);
	reg = r852_read_reg(dev, R852_CARD_STA);
	dev->card_detected = !!(reg & R852_CARD_STA_PRESENT);
	spin_unlock_irqrestore(&dev->irqlock, flags);
}