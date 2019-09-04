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
typedef  scalar_t__ u64 ;
struct n2rng {scalar_t__* test_buffer; } ;

/* Variables and functions */
 int SELFTEST_BUFFER_WORDS ; 

__attribute__((used)) static int n2rng_test_buffer_find(struct n2rng *np, u64 val)
{
	int i, count = 0;

	/* Purposefully skip over the first word.  */
	for (i = 1; i < SELFTEST_BUFFER_WORDS; i++) {
		if (np->test_buffer[i] == val)
			count++;
	}
	return count;
}