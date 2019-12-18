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
typedef  int uint32_t ;
struct fixed31_32 {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  x; } ;

/* Variables and functions */
 int MAX_HW_POINTS ; 
 int NUM_PTS_IN_REGION ; 
 int /*<<< orphan*/  compute_de_pq (int /*<<< orphan*/ ,struct fixed31_32*) ; 
 TYPE_1__* coordinates_x ; 
 struct fixed31_32 dc_fixpt_from_int (int) ; 
 int /*<<< orphan*/  dc_fixpt_mul (struct fixed31_32,struct fixed31_32) ; 
 int /*<<< orphan*/  dc_fixpt_zero ; 
 int /*<<< orphan*/ * de_pq_table ; 

void precompute_de_pq(void)
{
	int i;
	struct fixed31_32  y;
	uint32_t begin_index, end_index;

	struct fixed31_32 scaling_factor = dc_fixpt_from_int(125);

	/* X points is 2^-25 to 2^7
	 * De-gamma X is 2^-12 to 2^0 – we are skipping first -12-(-25) = 13 regions
	 */
	begin_index = 13 * NUM_PTS_IN_REGION;
	end_index = begin_index + 12 * NUM_PTS_IN_REGION;

	for (i = 0; i <= begin_index; i++)
		de_pq_table[i] = dc_fixpt_zero;

	for (; i <= end_index; i++) {
		compute_de_pq(coordinates_x[i].x, &y);
		de_pq_table[i] = dc_fixpt_mul(y, scaling_factor);
	}

	for (; i <= MAX_HW_POINTS; i++)
		de_pq_table[i] = de_pq_table[i-1];
}