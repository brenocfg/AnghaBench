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
struct net_device {int /*<<< orphan*/  base_addr; } ;
struct TYPE_3__ {int tx_bit; } ;
struct TYPE_4__ {int shreg; TYPE_1__ ser12; } ;
struct baycom_state {TYPE_2__ modem; int /*<<< orphan*/  hdrv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCR (int /*<<< orphan*/ ) ; 
 int hdlcdrv_getbits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ser12_set_divisor (struct net_device*,int) ; 

__attribute__((used)) static inline void ser12_tx(struct net_device *dev, struct baycom_state *bc)
{
	/* one interrupt per channel bit */
	ser12_set_divisor(dev, 12);
	/*
	 * first output the last bit (!) then call HDLC transmitter,
	 * since this may take quite long
	 */
	outb(0x0e | (!!bc->modem.ser12.tx_bit), MCR(dev->base_addr));
	if (bc->modem.shreg <= 1)
		bc->modem.shreg = 0x10000 | hdlcdrv_getbits(&bc->hdrv);
	bc->modem.ser12.tx_bit = !(bc->modem.ser12.tx_bit ^
				   (bc->modem.shreg & 1));
	bc->modem.shreg >>= 1;
}