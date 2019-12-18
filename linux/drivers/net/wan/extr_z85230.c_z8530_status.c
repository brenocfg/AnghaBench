#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct z8530_channel {int status; int dcdcheck; int* regs; TYPE_3__* netdevice; TYPE_2__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_fifo_errors; } ;
struct TYPE_7__ {TYPE_1__ stats; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_RES ; 
 int /*<<< orphan*/  R0 ; 
 int /*<<< orphan*/  R3 ; 
 int /*<<< orphan*/  RES_EXT_INT ; 
 int /*<<< orphan*/  RES_H_IUS ; 
 int RxENABLE ; 
 int TxEOM ; 
 int /*<<< orphan*/  netif_carrier_off (TYPE_3__*) ; 
 int /*<<< orphan*/  netif_carrier_on (TYPE_3__*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int read_zsreg (struct z8530_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_zsctrl (struct z8530_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_zsreg (struct z8530_channel*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  z8530_flush_fifo (struct z8530_channel*) ; 
 int /*<<< orphan*/  z8530_tx_done (struct z8530_channel*) ; 

__attribute__((used)) static void z8530_status(struct z8530_channel *chan)
{
	u8 status, altered;

	status = read_zsreg(chan, R0);
	altered = chan->status ^ status;

	chan->status = status;

	if (status & TxEOM) {
/*		printk("%s: Tx underrun.\n", chan->dev->name); */
		chan->netdevice->stats.tx_fifo_errors++;
		write_zsctrl(chan, ERR_RES);
		z8530_tx_done(chan);
	}

	if (altered & chan->dcdcheck)
	{
		if (status & chan->dcdcheck) {
			pr_info("%s: DCD raised\n", chan->dev->name);
			write_zsreg(chan, R3, chan->regs[3] | RxENABLE);
			if (chan->netdevice)
				netif_carrier_on(chan->netdevice);
		} else {
			pr_info("%s: DCD lost\n", chan->dev->name);
			write_zsreg(chan, R3, chan->regs[3] & ~RxENABLE);
			z8530_flush_fifo(chan);
			if (chan->netdevice)
				netif_carrier_off(chan->netdevice);
		}

	}
	write_zsctrl(chan, RES_EXT_INT);
	write_zsctrl(chan, RES_H_IUS);
}