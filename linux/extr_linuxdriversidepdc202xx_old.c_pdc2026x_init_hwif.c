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
typedef  int /*<<< orphan*/  ide_hwif_t ;

/* Variables and functions */
 int /*<<< orphan*/  pdc_old_disable_66MHz_clock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pdc2026x_init_hwif(ide_hwif_t *hwif)
{
	pdc_old_disable_66MHz_clock(hwif);
}