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
struct TYPE_4__ {TYPE_1__* device; } ;
struct rcar_dmac_chan {TYPE_2__ chan; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCAR_DMACHCR ; 
 int RCAR_DMACHCR_DE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int rcar_dmac_chan_read (struct rcar_dmac_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void rcar_dmac_chcr_de_barrier(struct rcar_dmac_chan *chan)
{
	u32 chcr;
	unsigned int i;

	/*
	 * Ensure that the setting of the DE bit is actually 0 after
	 * clearing it.
	 */
	for (i = 0; i < 1024; i++) {
		chcr = rcar_dmac_chan_read(chan, RCAR_DMACHCR);
		if (!(chcr & RCAR_DMACHCR_DE))
			return;
		udelay(1);
	}

	dev_err(chan->chan.device->dev, "CHCR DE check error\n");
}