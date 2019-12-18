#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  base_addr; } ;
struct TYPE_7__ {scalar_t__ magic; } ;
struct TYPE_6__ {scalar_t__ arb_divider; } ;
struct baycom_state {TYPE_2__ hdrv; TYPE_1__ modem; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ HDLCDRV_MAGIC ; 
 int /*<<< orphan*/  IIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  LSR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RBR (int /*<<< orphan*/ ) ; 
 scalar_t__ SER12_ARB_DIVIDER (struct baycom_state*) ; 
 int /*<<< orphan*/  THR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  baycom_int_freq (struct baycom_state*) ; 
 int /*<<< orphan*/  hdlcdrv_arbitrate (struct net_device*,TYPE_2__*) ; 
 int /*<<< orphan*/  hdlcdrv_ptt (TYPE_2__*) ; 
 int /*<<< orphan*/  hdlcdrv_receiver (struct net_device*,TYPE_2__*) ; 
 int /*<<< orphan*/  hdlcdrv_transmitter (struct net_device*,TYPE_2__*) ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 struct baycom_state* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ser12_rx (struct net_device*,struct baycom_state*) ; 
 int /*<<< orphan*/  ser12_tx (struct net_device*,struct baycom_state*) ; 

__attribute__((used)) static irqreturn_t ser12_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = (struct net_device *)dev_id;
	struct baycom_state *bc = netdev_priv(dev);
	unsigned char iir;

	if (!dev || !bc || bc->hdrv.magic != HDLCDRV_MAGIC)
		return IRQ_NONE;
	/* fast way out */
	if ((iir = inb(IIR(dev->base_addr))) & 1)
		return IRQ_NONE;
	baycom_int_freq(bc);
	do {
		switch (iir & 6) {
		case 6:
			inb(LSR(dev->base_addr));
			break;
			
		case 4:
			inb(RBR(dev->base_addr));
			break;
			
		case 2:
			/*
			 * check if transmitter active
			 */
			if (hdlcdrv_ptt(&bc->hdrv))
				ser12_tx(dev, bc);
			else {
				ser12_rx(dev, bc);
				bc->modem.arb_divider--;
			}
			outb(0x00, THR(dev->base_addr));
			break;
			
		default:
			inb(MSR(dev->base_addr));
			break;
		}
		iir = inb(IIR(dev->base_addr));
	} while (!(iir & 1));
	if (bc->modem.arb_divider <= 0) {
		bc->modem.arb_divider = SER12_ARB_DIVIDER(bc);
		local_irq_enable();
		hdlcdrv_arbitrate(dev, &bc->hdrv);
	}
	local_irq_enable();
	hdlcdrv_transmitter(dev, &bc->hdrv);
	hdlcdrv_receiver(dev, &bc->hdrv);
	local_irq_disable();
	return IRQ_HANDLED;
}