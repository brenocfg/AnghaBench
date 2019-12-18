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
struct omap_mbox_fifo {int /*<<< orphan*/  fifo_stat; } ;
struct omap_mbox {int /*<<< orphan*/  parent; struct omap_mbox_fifo tx_fifo; } ;

/* Variables and functions */
 int mbox_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mbox_fifo_full(struct omap_mbox *mbox)
{
	struct omap_mbox_fifo *fifo = &mbox->tx_fifo;

	return mbox_read_reg(mbox->parent, fifo->fifo_stat);
}