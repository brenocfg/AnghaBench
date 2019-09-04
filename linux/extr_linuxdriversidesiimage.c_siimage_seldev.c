#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u8 ;
struct TYPE_4__ {int host_flags; int channel; scalar_t__ hwif_data; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_5__ {int dn; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int IDE_HFLAG_MMIO ; 

__attribute__((used)) static inline unsigned long siimage_seldev(ide_drive_t *drive, int r)
{
	ide_hwif_t *hwif	= drive->hwif;
	unsigned long base	= (unsigned long)hwif->hwif_data;
	u8 unit			= drive->dn & 1;

	base += 0xA0 + r;
	if (hwif->host_flags & IDE_HFLAG_MMIO)
		base += hwif->channel << 6;
	else
		base += hwif->channel << 4;
	base |= unit << unit;
	return base;
}