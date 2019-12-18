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
struct omap_mbox {int /*<<< orphan*/  parent; struct omap_mbox_fifo rx_fifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  mbox_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 mbox_fifo_read(struct omap_mbox *mbox)
{
	struct omap_mbox_fifo *fifo = &mbox->rx_fifo;

	return mbox_read_reg(mbox->parent, fifo->msg);
}