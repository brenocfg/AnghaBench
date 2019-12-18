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
 int* ide_ifr ; 

int macide_test_irq(ide_hwif_t *hwif)
{
	if (*ide_ifr & 0x20)
		return 1;
	return 0;
}