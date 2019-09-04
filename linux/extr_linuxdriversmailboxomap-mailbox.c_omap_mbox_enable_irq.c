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
struct omap_mbox {int dummy; } ;
struct mbox_chan {int dummy; } ;
typedef  int /*<<< orphan*/  omap_mbox_irq_t ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  _omap_mbox_enable_irq (struct omap_mbox*,int /*<<< orphan*/ ) ; 
 struct omap_mbox* mbox_chan_to_omap_mbox (struct mbox_chan*) ; 

void omap_mbox_enable_irq(struct mbox_chan *chan, omap_mbox_irq_t irq)
{
	struct omap_mbox *mbox = mbox_chan_to_omap_mbox(chan);

	if (WARN_ON(!mbox))
		return;

	_omap_mbox_enable_irq(mbox, irq);
}