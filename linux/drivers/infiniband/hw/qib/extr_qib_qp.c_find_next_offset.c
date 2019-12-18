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
typedef  int u16 ;
struct rvt_qpn_table {int dummy; } ;
struct rvt_qpn_map {int /*<<< orphan*/  page; } ;

/* Variables and functions */
 int /*<<< orphan*/  RVT_BITS_PER_PAGE ; 
 unsigned int find_next_zero_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline unsigned find_next_offset(struct rvt_qpn_table *qpt,
					struct rvt_qpn_map *map, unsigned off,
					unsigned n, u16 qpt_mask)
{
	if (qpt_mask) {
		off++;
		if (((off & qpt_mask) >> 1) >= n)
			off = (off | qpt_mask) + 2;
	} else {
		off = find_next_zero_bit(map->page, RVT_BITS_PER_PAGE, off);
	}
	return off;
}