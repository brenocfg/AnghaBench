#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
struct TYPE_4__ {int def_type; TYPE_1__* var_ranges; } ;
struct TYPE_3__ {int mask_lo; int base_lo; scalar_t__ mask_hi; scalar_t__ base_hi; } ;

/* Variables and functions */
 int MTRR_TYPE_INVALID ; 
 int PAGE_MASK ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ check_type_overlap (int*,int*) ; 
 int get_mtrr_size (int) ; 
 TYPE_2__ mtrr_state ; 
 int num_var_ranges ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u8 mtrr_type_lookup_variable(u64 start, u64 end, u64 *partial_end,
				    int *repeat, u8 *uniform)
{
	int i;
	u64 base, mask;
	u8 prev_match, curr_match;

	*repeat = 0;
	*uniform = 1;

	/* Make end inclusive instead of exclusive */
	end--;

	prev_match = MTRR_TYPE_INVALID;
	for (i = 0; i < num_var_ranges; ++i) {
		unsigned short start_state, end_state, inclusive;

		if (!(mtrr_state.var_ranges[i].mask_lo & (1 << 11)))
			continue;

		base = (((u64)mtrr_state.var_ranges[i].base_hi) << 32) +
		       (mtrr_state.var_ranges[i].base_lo & PAGE_MASK);
		mask = (((u64)mtrr_state.var_ranges[i].mask_hi) << 32) +
		       (mtrr_state.var_ranges[i].mask_lo & PAGE_MASK);

		start_state = ((start & mask) == (base & mask));
		end_state = ((end & mask) == (base & mask));
		inclusive = ((start < base) && (end > base));

		if ((start_state != end_state) || inclusive) {
			/*
			 * We have start:end spanning across an MTRR.
			 * We split the region into either
			 *
			 * - start_state:1
			 * (start:mtrr_end)(mtrr_end:end)
			 * - end_state:1
			 * (start:mtrr_start)(mtrr_start:end)
			 * - inclusive:1
			 * (start:mtrr_start)(mtrr_start:mtrr_end)(mtrr_end:end)
			 *
			 * depending on kind of overlap.
			 *
			 * Return the type of the first region and a pointer
			 * to the start of next region so that caller will be
			 * advised to lookup again after having adjusted start
			 * and end.
			 *
			 * Note: This way we handle overlaps with multiple
			 * entries and the default type properly.
			 */
			if (start_state)
				*partial_end = base + get_mtrr_size(mask);
			else
				*partial_end = base;

			if (unlikely(*partial_end <= start)) {
				WARN_ON(1);
				*partial_end = start + PAGE_SIZE;
			}

			end = *partial_end - 1; /* end is inclusive */
			*repeat = 1;
			*uniform = 0;
		}

		if ((start & mask) != (base & mask))
			continue;

		curr_match = mtrr_state.var_ranges[i].base_lo & 0xff;
		if (prev_match == MTRR_TYPE_INVALID) {
			prev_match = curr_match;
			continue;
		}

		*uniform = 0;
		if (check_type_overlap(&prev_match, &curr_match))
			return curr_match;
	}

	if (prev_match != MTRR_TYPE_INVALID)
		return prev_match;

	return mtrr_state.def_type;
}