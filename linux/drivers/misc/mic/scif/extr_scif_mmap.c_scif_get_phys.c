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
struct scif_hw_dev {TYPE_1__* aper; scalar_t__ card_rel_da; } ;
struct scif_endpt {scalar_t__ remote_dev; } ;
struct scif_dev {struct scif_hw_dev* sdev; } ;
typedef  scalar_t__ phys_addr_t ;
struct TYPE_2__ {scalar_t__ pa; } ;

/* Variables and functions */
 int /*<<< orphan*/  scifdev_self (struct scif_dev*) ; 

__attribute__((used)) static phys_addr_t scif_get_phys(phys_addr_t phys, struct scif_endpt *ep)
{
	struct scif_dev *scifdev = (struct scif_dev *)ep->remote_dev;
	struct scif_hw_dev *sdev = scifdev->sdev;
	phys_addr_t out_phys, apt_base = 0;

	/*
	 * If the DMA address is card relative then we need to add the
	 * aperture base for mmap to work correctly
	 */
	if (!scifdev_self(scifdev) && sdev->aper && sdev->card_rel_da)
		apt_base = sdev->aper->pa;
	out_phys = apt_base + phys;
	return out_phys;
}