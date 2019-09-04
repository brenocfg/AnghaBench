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
typedef  int u32 ;
typedef  int /*<<< orphan*/  ide_hwif_t ;

/* Variables and functions */
 scalar_t__ CS5530_BAD_PIO (int) ; 
 unsigned long CS5530_BASEREG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** cs5530_pio_timings ; 
 int inl (unsigned long) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void init_hwif_cs5530 (ide_hwif_t *hwif)
{
	unsigned long basereg;
	u32 d0_timings;

	basereg = CS5530_BASEREG(hwif);
	d0_timings = inl(basereg + 0);
	if (CS5530_BAD_PIO(d0_timings))
		outl(cs5530_pio_timings[(d0_timings >> 31) & 1][0], basereg + 0);
	if (CS5530_BAD_PIO(inl(basereg + 8)))
		outl(cs5530_pio_timings[(d0_timings >> 31) & 1][0], basereg + 8);
}