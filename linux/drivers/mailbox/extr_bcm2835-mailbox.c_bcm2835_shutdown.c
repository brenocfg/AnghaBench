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
struct bcm2835_mbox {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ MAIL0_CNF ; 
 struct bcm2835_mbox* bcm2835_link_mbox (struct mbox_chan*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void bcm2835_shutdown(struct mbox_chan *link)
{
	struct bcm2835_mbox *mbox = bcm2835_link_mbox(link);

	writel(0, mbox->regs + MAIL0_CNF);
}