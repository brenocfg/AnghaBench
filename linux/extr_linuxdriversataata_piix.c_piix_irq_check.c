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
struct TYPE_3__ {int /*<<< orphan*/  bmdma_addr; } ;
struct ata_port {TYPE_2__* ops; TYPE_1__ ioaddr; } ;
struct TYPE_4__ {int (* bmdma_status ) (struct ata_port*) ;} ;

/* Variables and functions */
 int ATA_DMA_INTR ; 
 int stub1 (struct ata_port*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool piix_irq_check(struct ata_port *ap)
{
	if (unlikely(!ap->ioaddr.bmdma_addr))
		return false;

	return ap->ops->bmdma_status(ap) & ATA_DMA_INTR;
}