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
 int ENOSPC ; 
 int MAX_FLAGS ; 
 int find_next_bit (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flags_free ; 
 int /*<<< orphan*/  test_and_clear_bit (int,int /*<<< orphan*/ ) ; 

int pasemi_dma_alloc_flag(void)
{
	int bit;

retry:
	bit = find_next_bit(flags_free, MAX_FLAGS, 0);
	if (bit >= MAX_FLAGS)
		return -ENOSPC;
	if (!test_and_clear_bit(bit, flags_free))
		goto retry;

	return bit;
}