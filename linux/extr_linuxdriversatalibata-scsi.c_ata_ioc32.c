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
struct ata_port {int flags; int pflags; } ;

/* Variables and functions */
 int ATA_FLAG_PIO_DMA ; 
 int ATA_PFLAG_PIO32 ; 

__attribute__((used)) static int ata_ioc32(struct ata_port *ap)
{
	if (ap->flags & ATA_FLAG_PIO_DMA)
		return 1;
	if (ap->pflags & ATA_PFLAG_PIO32)
		return 1;
	return 0;
}