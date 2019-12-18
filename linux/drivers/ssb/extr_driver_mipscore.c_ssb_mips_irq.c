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
typedef  int u32 ;
struct ssb_device {struct ssb_bus* bus; } ;
struct TYPE_2__ {struct ssb_device* dev; } ;
struct ssb_bus {TYPE_1__ mipscore; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSB_INTVEC ; 
 int /*<<< orphan*/  SSB_IPSFLAG ; 
 int* ipsflag_irq_mask ; 
 int* ipsflag_irq_shift ; 
 int ssb_irqflag (struct ssb_device*) ; 
 int ssb_read32 (struct ssb_device*,int /*<<< orphan*/ ) ; 

unsigned int ssb_mips_irq(struct ssb_device *dev)
{
	struct ssb_bus *bus = dev->bus;
	struct ssb_device *mdev = bus->mipscore.dev;
	u32 irqflag;
	u32 ipsflag;
	u32 tmp;
	unsigned int irq;

	irqflag = ssb_irqflag(dev);
	if (irqflag == 0x3f)
		return 6;
	ipsflag = ssb_read32(bus->mipscore.dev, SSB_IPSFLAG);
	for (irq = 1; irq <= 4; irq++) {
		tmp = ((ipsflag & ipsflag_irq_mask[irq]) >> ipsflag_irq_shift[irq]);
		if (tmp == irqflag)
			break;
	}
	if (irq	== 5) {
		if ((1 << irqflag) & ssb_read32(mdev, SSB_INTVEC))
			irq = 0;
	}

	return irq;
}