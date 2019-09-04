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
struct rockchip_mbox_chan {size_t idx; int /*<<< orphan*/ * msg; } ;
struct rockchip_mbox {struct rockchip_mbox_chan* chans; scalar_t__ mbox_base; } ;
struct mbox_chan {TYPE_1__* mbox; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ MAILBOX_B2A_INTEN ; 
 struct rockchip_mbox* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void rockchip_mbox_shutdown(struct mbox_chan *chan)
{
	struct rockchip_mbox *mb = dev_get_drvdata(chan->mbox->dev);
	struct rockchip_mbox_chan *chans = mb->chans;

	/* Disable all B2A interrupts */
	writel_relaxed(0, mb->mbox_base + MAILBOX_B2A_INTEN);

	mb->chans[chans->idx].msg = NULL;
}