#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scif_window_iter {int dummy; } ;
struct scif_window {scalar_t__ type; } ;
struct scif_dev {TYPE_2__* sdev; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_4__ {TYPE_1__* aper; int /*<<< orphan*/  card_rel_da; } ;
struct TYPE_3__ {scalar_t__ pa; } ;

/* Variables and functions */
 scalar_t__ SCIF_WINDOW_PEER ; 
 void* scif_ioremap (scalar_t__,size_t,struct scif_dev*) ; 
 scalar_t__ scif_off_to_dma_addr (struct scif_window*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct scif_window_iter*) ; 
 int /*<<< orphan*/  scifdev_self (struct scif_dev*) ; 

__attribute__((used)) static inline
void *ioremap_remote(off_t off, struct scif_window *window,
		     size_t len, struct scif_dev *dev,
		     struct scif_window_iter *iter)
{
	dma_addr_t phys = scif_off_to_dma_addr(window, off, NULL, iter);

	/*
	 * If the DMA address is not card relative then we need the DMA
	 * addresses to be an offset into the bar. The aperture base was already
	 * added so subtract it here since scif_ioremap is going to add it again
	 */
	if (!scifdev_self(dev) && window->type == SCIF_WINDOW_PEER &&
	    dev->sdev->aper && !dev->sdev->card_rel_da)
		phys = phys - dev->sdev->aper->pa;
	return scif_ioremap(phys, len, dev);
}