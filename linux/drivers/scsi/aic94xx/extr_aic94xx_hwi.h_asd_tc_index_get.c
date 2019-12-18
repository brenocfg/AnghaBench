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
struct asd_seq_data {int tc_index_bitmap_bits; int /*<<< orphan*/  tc_index_bitmap; void** tc_index_array; } ;

/* Variables and functions */
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int asd_tc_index_get(struct asd_seq_data *seq, void *ptr)
{
	int index;

	index = find_first_zero_bit(seq->tc_index_bitmap,
				    seq->tc_index_bitmap_bits);
	if (index == seq->tc_index_bitmap_bits)
		return -1;

	seq->tc_index_array[index] = ptr;
	set_bit(index, seq->tc_index_bitmap);

	return index;
}