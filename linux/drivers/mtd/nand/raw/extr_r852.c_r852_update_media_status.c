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
struct r852_device {int sm; int readonly; int /*<<< orphan*/  irqlock; int /*<<< orphan*/  card_detected; } ;

/* Variables and functions */
 int /*<<< orphan*/  R852_CARD_STA ; 
 int R852_CARD_STA_RO ; 
 int R852_DMA1 ; 
 int R852_DMA2 ; 
 int /*<<< orphan*/  R852_DMA_CAP ; 
 int R852_SMBIT ; 
 int /*<<< orphan*/  message (char*,...) ; 
 int r852_read_reg (struct r852_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void r852_update_media_status(struct r852_device *dev)
{
	uint8_t reg;
	unsigned long flags;
	int readonly;

	spin_lock_irqsave(&dev->irqlock, flags);
	if (!dev->card_detected) {
		message("card removed");
		spin_unlock_irqrestore(&dev->irqlock, flags);
		return ;
	}

	readonly  = r852_read_reg(dev, R852_CARD_STA) & R852_CARD_STA_RO;
	reg = r852_read_reg(dev, R852_DMA_CAP);
	dev->sm = (reg & (R852_DMA1 | R852_DMA2)) && (reg & R852_SMBIT);

	message("detected %s %s card in slot",
		dev->sm ? "SmartMedia" : "xD",
		readonly ? "readonly" : "writeable");

	dev->readonly = readonly;
	spin_unlock_irqrestore(&dev->irqlock, flags);
}