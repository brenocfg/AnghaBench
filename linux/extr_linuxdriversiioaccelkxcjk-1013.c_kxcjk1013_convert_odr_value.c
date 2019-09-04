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
struct kx_odr_map {int odr_bits; int val; int val2; } ;

/* Variables and functions */
 int EINVAL ; 
 int IIO_VAL_INT_PLUS_MICRO ; 

__attribute__((used)) static int kxcjk1013_convert_odr_value(const struct kx_odr_map *map,
				       size_t map_size, int odr_bits,
				       int *val, int *val2)
{
	int i;

	for (i = 0; i < map_size; ++i) {
		if (map[i].odr_bits == odr_bits) {
			*val = map[i].val;
			*val2 = map[i].val2;
			return IIO_VAL_INT_PLUS_MICRO;
		}
	}

	return -EINVAL;
}