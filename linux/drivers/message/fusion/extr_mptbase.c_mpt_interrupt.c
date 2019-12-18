#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_6__ {TYPE_1__* chip; } ;
struct TYPE_5__ {int /*<<< orphan*/  ReplyFifo; } ;
typedef  TYPE_2__ MPT_ADAPTER ;

/* Variables and functions */
 int CHIPREG_READ32_dmasync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int MPI_ADDRESS_REPLY_A_BIT ; 
 int /*<<< orphan*/  mpt_reply (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mpt_turbo_reply (TYPE_2__*,int) ; 

__attribute__((used)) static irqreturn_t
mpt_interrupt(int irq, void *bus_id)
{
	MPT_ADAPTER *ioc = bus_id;
	u32 pa = CHIPREG_READ32_dmasync(&ioc->chip->ReplyFifo);

	if (pa == 0xFFFFFFFF)
		return IRQ_NONE;

	/*
	 *  Drain the reply FIFO!
	 */
	do {
		if (pa & MPI_ADDRESS_REPLY_A_BIT)
			mpt_reply(ioc, pa);
		else
			mpt_turbo_reply(ioc, pa);
		pa = CHIPREG_READ32_dmasync(&ioc->chip->ReplyFifo);
	} while (pa != 0xFFFFFFFF);

	return IRQ_HANDLED;
}