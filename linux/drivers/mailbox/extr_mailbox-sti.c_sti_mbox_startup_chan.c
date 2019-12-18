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

/* Variables and functions */
 int /*<<< orphan*/  sti_mbox_clear_irq (struct mbox_chan*) ; 
 int /*<<< orphan*/  sti_mbox_enable_channel (struct mbox_chan*) ; 

__attribute__((used)) static int sti_mbox_startup_chan(struct mbox_chan *chan)
{
	sti_mbox_clear_irq(chan);
	sti_mbox_enable_channel(chan);

	return 0;
}