#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct bcma_device {TYPE_2__* bus; } ;
struct TYPE_3__ {struct bcma_device* core; } ;
struct TYPE_4__ {TYPE_1__ drv_mips; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_MIPS_MIPS74K_INTMASK (unsigned int) ; 
 int bcma_core_mips_irqflag (struct bcma_device*) ; 
 int bcma_read32 (struct bcma_device*,int /*<<< orphan*/ ) ; 

unsigned int bcma_core_mips_irq(struct bcma_device *dev)
{
	struct bcma_device *mdev = dev->bus->drv_mips.core;
	u32 irqflag;
	unsigned int irq;

	irqflag = bcma_core_mips_irqflag(dev);
	if (irqflag == 0x3f)
		return 6;

	for (irq = 0; irq <= 4; irq++)
		if (bcma_read32(mdev, BCMA_MIPS_MIPS74K_INTMASK(irq)) &
		    (1 << irqflag))
			return irq;

	return 5;
}