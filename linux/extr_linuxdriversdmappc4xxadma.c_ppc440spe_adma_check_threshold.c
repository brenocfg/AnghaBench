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
struct ppc440spe_adma_chan {scalar_t__ pending; TYPE_2__* device; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; TYPE_1__ common; } ;

/* Variables and functions */
 scalar_t__ PPC440SPE_ADMA_THRESHOLD ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ppc440spe_chan_append (struct ppc440spe_adma_chan*) ; 

__attribute__((used)) static void ppc440spe_adma_check_threshold(struct ppc440spe_adma_chan *chan)
{
	dev_dbg(chan->device->common.dev, "ppc440spe adma%d: pending: %d\n",
		chan->device->id, chan->pending);

	if (chan->pending >= PPC440SPE_ADMA_THRESHOLD) {
		chan->pending = 0;
		ppc440spe_chan_append(chan);
	}
}