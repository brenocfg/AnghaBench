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
struct atmel_pmecc_gf_tables {unsigned int* alpha_to; unsigned int* index_of; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int deg (unsigned int) ; 

__attribute__((used)) static int atmel_pmecc_build_gf_tables(int mm, unsigned int poly,
				       struct atmel_pmecc_gf_tables *gf_tables)
{
	unsigned int i, x = 1;
	const unsigned int k = BIT(deg(poly));
	unsigned int nn = BIT(mm) - 1;

	/* primitive polynomial must be of degree m */
	if (k != (1u << mm))
		return -EINVAL;

	for (i = 0; i < nn; i++) {
		gf_tables->alpha_to[i] = x;
		gf_tables->index_of[x] = i;
		if (i && (x == 1))
			/* polynomial is not primitive (a^i=1 with 0<i<2^m-1) */
			return -EINVAL;
		x <<= 1;
		if (x & k)
			x ^= poly;
	}
	gf_tables->alpha_to[nn] = 1;
	gf_tables->index_of[0] = 0;

	return 0;
}