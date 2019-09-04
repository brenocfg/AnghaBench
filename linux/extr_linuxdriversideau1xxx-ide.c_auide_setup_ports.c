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
struct ide_hw {unsigned long* io_ports_array; } ;
struct TYPE_3__ {int regbase; } ;
typedef  TYPE_1__ _auide_hwif ;

/* Variables and functions */
 int IDE_REG_SHIFT ; 

__attribute__((used)) static void auide_setup_ports(struct ide_hw *hw, _auide_hwif *ahwif)
{
	int i;
	unsigned long *ata_regs = hw->io_ports_array;

	/* FIXME? */
	for (i = 0; i < 8; i++)
		*ata_regs++ = ahwif->regbase + (i << IDE_REG_SHIFT);

	/* set the Alternative Status register */
	*ata_regs = ahwif->regbase + (14 << IDE_REG_SHIFT);
}