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
struct hw_x_point {int /*<<< orphan*/  x; } ;
struct fixed31_32 {int dummy; } ;

/* Variables and functions */
 int MAX_HW_POINTS ; 
 int /*<<< orphan*/  compute_pq (struct fixed31_32,int /*<<< orphan*/ *) ; 
 struct hw_x_point* coordinates_x ; 
 struct fixed31_32 dc_fixpt_from_fraction (int,int) ; 
 struct fixed31_32 dc_fixpt_mul (int /*<<< orphan*/ ,struct fixed31_32) ; 
 int /*<<< orphan*/  dc_fixpt_zero ; 
 int /*<<< orphan*/ * pq_table ; 

void precompute_pq(void)
{
	int i;
	struct fixed31_32 x;
	const struct hw_x_point *coord_x = coordinates_x + 32;
	struct fixed31_32 scaling_factor =
			dc_fixpt_from_fraction(80, 10000);

	/* pow function has problems with arguments too small */
	for (i = 0; i < 32; i++)
		pq_table[i] = dc_fixpt_zero;

	for (i = 32; i <= MAX_HW_POINTS; i++) {
		x = dc_fixpt_mul(coord_x->x, scaling_factor);
		compute_pq(x, &pq_table[i]);
		++coord_x;
	}
}