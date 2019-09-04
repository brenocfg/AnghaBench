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
struct scif_window {scalar_t__ type; int nr_contig_chunks; int /*<<< orphan*/ * dma_addr; scalar_t__* num_pages; } ;
struct scif_hw_dev {TYPE_1__* aper; int /*<<< orphan*/  card_rel_da; } ;
struct scif_dev {struct scif_hw_dev* sdev; } ;
typedef  scalar_t__ phys_addr_t ;
struct TYPE_2__ {scalar_t__ pa; } ;

/* Variables and functions */
 scalar_t__ SCIF_WINDOW_PEER ; 
 int /*<<< orphan*/  scifdev_self (struct scif_dev*) ; 

__attribute__((used)) static void
scif_fixup_aper_base(struct scif_dev *dev, struct scif_window *window)
{
	int j;
	struct scif_hw_dev *sdev = dev->sdev;
	phys_addr_t apt_base = 0;

	/*
	 * Add the aperture base if the DMA address is not card relative
	 * since the DMA addresses need to be an offset into the bar
	 */
	if (!scifdev_self(dev) && window->type == SCIF_WINDOW_PEER &&
	    sdev->aper && !sdev->card_rel_da)
		apt_base = sdev->aper->pa;
	else
		return;

	for (j = 0; j < window->nr_contig_chunks; j++) {
		if (window->num_pages[j])
			window->dma_addr[j] += apt_base;
		else
			break;
	}
}