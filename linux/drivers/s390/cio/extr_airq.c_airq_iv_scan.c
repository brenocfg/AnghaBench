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
struct airq_iv {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit_inv (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long find_next_bit_inv (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 

unsigned long airq_iv_scan(struct airq_iv *iv, unsigned long start,
			   unsigned long end)
{
	unsigned long bit;

	/* Find non-zero bit starting from 'ivs->next'. */
	bit = find_next_bit_inv(iv->vector, end, start);
	if (bit >= end)
		return -1UL;
	clear_bit_inv(bit, iv->vector);
	return bit;
}