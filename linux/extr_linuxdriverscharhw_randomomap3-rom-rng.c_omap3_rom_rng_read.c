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
struct hwrng {int dummy; } ;

/* Variables and functions */
 int omap3_rom_rng_get_random (void*,int) ; 

__attribute__((used)) static int omap3_rom_rng_read(struct hwrng *rng, void *data, size_t max, bool w)
{
	int r;

	r = omap3_rom_rng_get_random(data, 4);
	if (r < 0)
		return r;
	return 4;
}