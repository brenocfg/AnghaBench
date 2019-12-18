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
typedef  int /*<<< orphan*/  u32 ;
struct omap_mbox_fifo {int /*<<< orphan*/  msg; } ;
struct omap_mbox {int /*<<< orphan*/  parent; struct omap_mbox_fifo tx_fifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  mbox_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mbox_fifo_write(struct omap_mbox *mbox, u32 msg)
{
	struct omap_mbox_fifo *fifo = &mbox->tx_fifo;

	mbox_write_reg(mbox->parent, msg, fifo->msg);
}