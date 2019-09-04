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
struct mbox_chan {int dummy; } ;
struct bcm2835_mbox {int /*<<< orphan*/  lock; scalar_t__ regs; } ;

/* Variables and functions */
 int ARM_MS_FULL ; 
 scalar_t__ MAIL1_STA ; 
 struct bcm2835_mbox* bcm2835_link_mbox (struct mbox_chan*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool bcm2835_last_tx_done(struct mbox_chan *link)
{
	struct bcm2835_mbox *mbox = bcm2835_link_mbox(link);
	bool ret;

	spin_lock(&mbox->lock);
	ret = !(readl(mbox->regs + MAIL1_STA) & ARM_MS_FULL);
	spin_unlock(&mbox->lock);
	return ret;
}