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
 int NMTUS ; 

unsigned int cxgb4_best_aligned_mtu(const unsigned short *mtus,
				    unsigned short header_size,
				    unsigned short data_size_max,
				    unsigned short data_size_align,
				    unsigned int *mtu_idxp)
{
	unsigned short max_mtu = header_size + data_size_max;
	unsigned short data_size_align_mask = data_size_align - 1;
	int mtu_idx, aligned_mtu_idx;

	/* Scan the MTU Table till we find an MTU which is larger than our
	 * Maximum MTU or we reach the end of the table.  Along the way,
	 * record the last MTU found, if any, which will result in a Data
	 * Segment Length matching the requested alignment.
	 */
	for (mtu_idx = 0, aligned_mtu_idx = -1; mtu_idx < NMTUS; mtu_idx++) {
		unsigned short data_size = mtus[mtu_idx] - header_size;

		/* If this MTU minus the Header Size would result in a
		 * Data Segment Size of the desired alignment, remember it.
		 */
		if ((data_size & data_size_align_mask) == 0)
			aligned_mtu_idx = mtu_idx;

		/* If we're not at the end of the Hardware MTU Table and the
		 * next element is larger than our Maximum MTU, drop out of
		 * the loop.
		 */
		if (mtu_idx+1 < NMTUS && mtus[mtu_idx+1] > max_mtu)
			break;
	}

	/* If we fell out of the loop because we ran to the end of the table,
	 * then we just have to use the last [largest] entry.
	 */
	if (mtu_idx == NMTUS)
		mtu_idx--;

	/* If we found an MTU which resulted in the requested Data Segment
	 * Length alignment and that's "not far" from the largest MTU which is
	 * less than or equal to the maximum MTU, then use that.
	 */
	if (aligned_mtu_idx >= 0 &&
	    mtu_idx - aligned_mtu_idx <= 1)
		mtu_idx = aligned_mtu_idx;

	/* If the caller has passed in an MTU Index pointer, pass the
	 * MTU Index back.  Return the MTU value.
	 */
	if (mtu_idxp)
		*mtu_idxp = mtu_idx;
	return mtus[mtu_idx];
}