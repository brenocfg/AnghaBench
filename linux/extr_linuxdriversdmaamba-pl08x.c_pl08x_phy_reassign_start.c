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
struct pl08x_phy_chan {struct pl08x_dma_chan* serving; int /*<<< orphan*/  id; } ;
struct pl08x_driver_data {TYPE_1__* adev; } ;
struct pl08x_dma_chan {int /*<<< orphan*/  state; struct pl08x_phy_chan* phychan; int /*<<< orphan*/  name; struct pl08x_driver_data* host; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PL08X_CHAN_RUNNING ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pl08x_start_next_txd (struct pl08x_dma_chan*) ; 

__attribute__((used)) static void pl08x_phy_reassign_start(struct pl08x_phy_chan *ch,
	struct pl08x_dma_chan *plchan)
{
	struct pl08x_driver_data *pl08x = plchan->host;

	dev_dbg(&pl08x->adev->dev, "reassigned physical channel %d for xfer on %s\n",
		ch->id, plchan->name);

	/*
	 * We do this without taking the lock; we're really only concerned
	 * about whether this pointer is NULL or not, and we're guaranteed
	 * that this will only be called when it _already_ is non-NULL.
	 */
	ch->serving = plchan;
	plchan->phychan = ch;
	plchan->state = PL08X_CHAN_RUNNING;
	pl08x_start_next_txd(plchan);
}