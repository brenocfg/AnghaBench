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

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int regmap_mmio_get_min_stride(size_t val_bits)
{
	int min_stride;

	switch (val_bits) {
	case 8:
		/* The core treats 0 as 1 */
		min_stride = 0;
		return 0;
	case 16:
		min_stride = 2;
		break;
	case 32:
		min_stride = 4;
		break;
#ifdef CONFIG_64BIT
	case 64:
		min_stride = 8;
		break;
#endif
	default:
		return -EINVAL;
	}

	return min_stride;
}