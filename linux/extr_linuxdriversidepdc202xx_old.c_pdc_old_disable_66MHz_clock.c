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
typedef  int u8 ;
struct TYPE_3__ {int extra_base; scalar_t__ channel; } ;
typedef  TYPE_1__ ide_hwif_t ;

/* Variables and functions */
 int inb (unsigned long) ; 
 int /*<<< orphan*/  outb (int,unsigned long) ; 

__attribute__((used)) static void pdc_old_disable_66MHz_clock(ide_hwif_t *hwif)
{
	unsigned long clock_reg = hwif->extra_base + 0x01;
	u8 clock = inb(clock_reg);

	outb(clock & ~(hwif->channel ? 0x08 : 0x02), clock_reg);
}