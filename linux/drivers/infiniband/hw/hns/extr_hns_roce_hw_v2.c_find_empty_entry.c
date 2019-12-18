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
struct hns_roce_idx_que {int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  bitmap_full (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,int,int) ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int find_empty_entry(struct hns_roce_idx_que *idx_que,
			    unsigned long size)
{
	int wqe_idx;

	if (unlikely(bitmap_full(idx_que->bitmap, size)))
		return -ENOSPC;

	wqe_idx = find_first_zero_bit(idx_que->bitmap, size);

	bitmap_set(idx_que->bitmap, wqe_idx, 1);

	return wqe_idx;
}