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
struct path_info {int relative_throughput; int /*<<< orphan*/  in_flight_size; } ;

/* Variables and functions */
 size_t ST_MAX_INFLIGHT_SIZE ; 
 size_t ST_MAX_RELATIVE_THROUGHPUT_SHIFT ; 
 size_t atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int st_compare_load(struct path_info *pi1, struct path_info *pi2,
			   size_t incoming)
{
	size_t sz1, sz2, st1, st2;

	sz1 = atomic_read(&pi1->in_flight_size);
	sz2 = atomic_read(&pi2->in_flight_size);

	/*
	 * Case 1: Both have same throughput value. Choose less loaded path.
	 */
	if (pi1->relative_throughput == pi2->relative_throughput)
		return sz1 - sz2;

	/*
	 * Case 2a: Both have same load. Choose higher throughput path.
	 * Case 2b: One path has no throughput value. Choose the other one.
	 */
	if (sz1 == sz2 ||
	    !pi1->relative_throughput || !pi2->relative_throughput)
		return pi2->relative_throughput - pi1->relative_throughput;

	/*
	 * Case 3: Calculate service time. Choose faster path.
	 *         Service time using pi1:
	 *             st1 = (sz1 + incoming) / pi1->relative_throughput
	 *         Service time using pi2:
	 *             st2 = (sz2 + incoming) / pi2->relative_throughput
	 *
	 *         To avoid the division, transform the expression to use
	 *         multiplication.
	 *         Because ->relative_throughput > 0 here, if st1 < st2,
	 *         the expressions below are the same meaning:
	 *             (sz1 + incoming) / pi1->relative_throughput <
	 *                 (sz2 + incoming) / pi2->relative_throughput
	 *             (sz1 + incoming) * pi2->relative_throughput <
	 *                 (sz2 + incoming) * pi1->relative_throughput
	 *         So use the later one.
	 */
	sz1 += incoming;
	sz2 += incoming;
	if (unlikely(sz1 >= ST_MAX_INFLIGHT_SIZE ||
		     sz2 >= ST_MAX_INFLIGHT_SIZE)) {
		/*
		 * Size may be too big for multiplying pi->relative_throughput
		 * and overflow.
		 * To avoid the overflow and mis-selection, shift down both.
		 */
		sz1 >>= ST_MAX_RELATIVE_THROUGHPUT_SHIFT;
		sz2 >>= ST_MAX_RELATIVE_THROUGHPUT_SHIFT;
	}
	st1 = sz1 * pi2->relative_throughput;
	st2 = sz2 * pi1->relative_throughput;
	if (st1 != st2)
		return st1 - st2;

	/*
	 * Case 4: Service time is equal. Choose higher throughput path.
	 */
	return pi2->relative_throughput - pi1->relative_throughput;
}