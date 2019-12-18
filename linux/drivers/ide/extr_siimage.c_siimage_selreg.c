#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int host_flags; int channel; scalar_t__ hwif_data; } ;
typedef  TYPE_1__ ide_hwif_t ;

/* Variables and functions */
 int IDE_HFLAG_MMIO ; 

__attribute__((used)) static unsigned long siimage_selreg(ide_hwif_t *hwif, int r)
{
	unsigned long base = (unsigned long)hwif->hwif_data;

	base += 0xA0 + r;
	if (hwif->host_flags & IDE_HFLAG_MMIO)
		base += hwif->channel << 6;
	else
		base += hwif->channel << 4;
	return base;
}