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
struct mlxsw_sp2_kvdl_part {int last_allocated_bit; unsigned int usage_bit_count; int /*<<< orphan*/  usage; } ;

/* Variables and functions */
 int ENOBUFS ; 
 unsigned int find_next_zero_bit (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 scalar_t__ test_bit (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_sp2_kvdl_part_find_zero_bits(struct mlxsw_sp2_kvdl_part *part,
					      unsigned int bit_count,
					      unsigned int *p_bit)
{
	unsigned int start_bit;
	unsigned int bit;
	unsigned int i;
	bool wrap = false;

	start_bit = part->last_allocated_bit + 1;
	if (start_bit == part->usage_bit_count)
		start_bit = 0;
	bit = start_bit;
again:
	bit = find_next_zero_bit(part->usage, part->usage_bit_count, bit);
	if (!wrap && bit + bit_count >= part->usage_bit_count) {
		wrap = true;
		bit = 0;
		goto again;
	}
	if (wrap && bit + bit_count >= start_bit)
		return -ENOBUFS;
	for (i = 0; i < bit_count; i++) {
		if (test_bit(bit + i, part->usage)) {
			bit += bit_count;
			goto again;
		}
	}
	*p_bit = bit;
	return 0;
}