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
struct pm8001_hba_info {TYPE_1__* io_mem; } ;
typedef  int s8 ;
struct TYPE_2__ {scalar_t__ memvirtaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (scalar_t__) ; 

void pm8001_chip_iounmap(struct pm8001_hba_info *pm8001_ha)
{
	s8 bar, logical = 0;
	for (bar = 0; bar < 6; bar++) {
		/*
		** logical BARs for SPC:
		** bar 0 and 1 - logical BAR0
		** bar 2 and 3 - logical BAR1
		** bar4 - logical BAR2
		** bar5 - logical BAR3
		** Skip the appropriate assignments:
		*/
		if ((bar == 1) || (bar == 3))
			continue;
		if (pm8001_ha->io_mem[logical].memvirtaddr) {
			iounmap(pm8001_ha->io_mem[logical].memvirtaddr);
			logical++;
		}
	}
}