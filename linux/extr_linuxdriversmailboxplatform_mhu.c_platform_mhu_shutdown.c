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
struct platform_mhu_link {int /*<<< orphan*/  irq; } ;
struct mbox_chan {struct platform_mhu_link* con_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct mbox_chan*) ; 

__attribute__((used)) static void platform_mhu_shutdown(struct mbox_chan *chan)
{
	struct platform_mhu_link *mlink = chan->con_priv;

	free_irq(mlink->irq, chan);
}