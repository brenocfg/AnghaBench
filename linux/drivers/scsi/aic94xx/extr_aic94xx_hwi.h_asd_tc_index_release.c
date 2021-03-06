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
struct asd_seq_data {int /*<<< orphan*/  tc_index_bitmap; int /*<<< orphan*/ ** tc_index_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void asd_tc_index_release(struct asd_seq_data *seq, int index)
{
	seq->tc_index_array[index] = NULL;
	clear_bit(index, seq->tc_index_bitmap);
}