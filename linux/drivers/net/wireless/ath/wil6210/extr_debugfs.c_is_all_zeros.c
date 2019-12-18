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
typedef  scalar_t__ u32 ;

/* Variables and functions */

__attribute__((used)) static bool is_all_zeros(void * const x_, size_t sz)
{
	/* if reply is all-0, ignore this CID */
	u32 *x = x_;
	int n;

	for (n = 0; n < sz / sizeof(*x); n++)
		if (x[n])
			return false;

	return true;
}