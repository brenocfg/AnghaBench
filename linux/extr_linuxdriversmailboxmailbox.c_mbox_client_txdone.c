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
struct mbox_chan {int txdone_method; TYPE_1__* mbox; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int TXDONE_BY_ACK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tx_tick (struct mbox_chan*,int) ; 
 scalar_t__ unlikely (int) ; 

void mbox_client_txdone(struct mbox_chan *chan, int r)
{
	if (unlikely(!(chan->txdone_method & TXDONE_BY_ACK))) {
		dev_err(chan->mbox->dev, "Client can't run the TX ticker\n");
		return;
	}

	tx_tick(chan, r);
}