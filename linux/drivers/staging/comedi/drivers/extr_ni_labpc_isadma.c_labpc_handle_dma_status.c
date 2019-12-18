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
struct labpc_private {int stat1; int stat2; } ;
struct labpc_boardinfo {scalar_t__ is_labpc1200; } ;
struct comedi_device {struct labpc_private* private; struct labpc_boardinfo* board_ptr; } ;

/* Variables and functions */
 int STAT1_GATA0 ; 
 int STAT2_OUTA1 ; 
 int /*<<< orphan*/  handle_isa_dma (struct comedi_device*) ; 

void labpc_handle_dma_status(struct comedi_device *dev)
{
	const struct labpc_boardinfo *board = dev->board_ptr;
	struct labpc_private *devpriv = dev->private;

	/*
	 * if a dma terminal count of external stop trigger
	 * has occurred
	 */
	if (devpriv->stat1 & STAT1_GATA0 ||
	    (board->is_labpc1200 && devpriv->stat2 & STAT2_OUTA1))
		handle_isa_dma(dev);
}