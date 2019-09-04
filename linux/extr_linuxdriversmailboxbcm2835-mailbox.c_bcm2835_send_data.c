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
typedef  int /*<<< orphan*/  u32 ;
struct mbox_chan {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct bcm2835_mbox {int /*<<< orphan*/  lock; TYPE_1__ controller; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ MAIL1_WRT ; 
 struct bcm2835_mbox* bcm2835_link_mbox (struct mbox_chan*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int bcm2835_send_data(struct mbox_chan *link, void *data)
{
	struct bcm2835_mbox *mbox = bcm2835_link_mbox(link);
	u32 msg = *(u32 *)data;

	spin_lock(&mbox->lock);
	writel(msg, mbox->regs + MAIL1_WRT);
	dev_dbg(mbox->controller.dev, "Request 0x%08X\n", msg);
	spin_unlock(&mbox->lock);
	return 0;
}