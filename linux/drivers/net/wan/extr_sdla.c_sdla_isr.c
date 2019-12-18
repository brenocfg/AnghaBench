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
struct net_device {char irq; scalar_t__ base_addr; } ;
struct frad_local {scalar_t__ type; int /*<<< orphan*/  state; int /*<<< orphan*/  initialized; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  SDLA_502_IRQ_INTERFACE ; 
 int /*<<< orphan*/  SDLA_508_IRQ_INTERFACE ; 
#define  SDLA_INTR_COMPLETE 133 
#define  SDLA_INTR_MODEM 132 
#define  SDLA_INTR_RX 131 
#define  SDLA_INTR_STATUS 130 
#define  SDLA_INTR_TIMER 129 
#define  SDLA_INTR_TX 128 
 int /*<<< orphan*/  SDLA_READ_DLC_STATUS ; 
 scalar_t__ SDLA_REG_CONTROL ; 
 scalar_t__ SDLA_S502E ; 
 int /*<<< orphan*/  SDLA_S502E_INTACK ; 
 scalar_t__ SDLA_S508 ; 
 struct frad_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,char) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 char sdla_byte (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdla_cmd (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdla_receive (struct net_device*) ; 
 int /*<<< orphan*/  sdla_write (struct net_device*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static irqreturn_t sdla_isr(int dummy, void *dev_id)
{
	struct net_device     *dev;
	struct frad_local *flp;
	char              byte;

	dev = dev_id;

	flp = netdev_priv(dev);

	if (!flp->initialized)
	{
		netdev_warn(dev, "irq %d for uninitialized device\n", dev->irq);
		return IRQ_NONE;
	}

	byte = sdla_byte(dev, flp->type == SDLA_S508 ? SDLA_508_IRQ_INTERFACE : SDLA_502_IRQ_INTERFACE);
	switch (byte)
	{
		case SDLA_INTR_RX:
			sdla_receive(dev);
			break;

		/* the command will get an error return, which is processed above */
		case SDLA_INTR_MODEM:
		case SDLA_INTR_STATUS:
			sdla_cmd(dev, SDLA_READ_DLC_STATUS, 0, 0, NULL, 0, NULL, NULL);
			break;

		case SDLA_INTR_TX:
		case SDLA_INTR_COMPLETE:
		case SDLA_INTR_TIMER:
			netdev_warn(dev, "invalid irq flag 0x%02X\n", byte);
			break;
	}

	/* the S502E requires a manual acknowledgement of the interrupt */ 
	if (flp->type == SDLA_S502E)
	{
		flp->state &= ~SDLA_S502E_INTACK;
		outb(flp->state, dev->base_addr + SDLA_REG_CONTROL);
		flp->state |= SDLA_S502E_INTACK;
		outb(flp->state, dev->base_addr + SDLA_REG_CONTROL);
	}

	/* this clears the byte, informing the Z80 we're done */
	byte = 0;
	sdla_write(dev, flp->type == SDLA_S508 ? SDLA_508_IRQ_INTERFACE : SDLA_502_IRQ_INTERFACE, &byte, sizeof(byte));
	return IRQ_HANDLED;
}