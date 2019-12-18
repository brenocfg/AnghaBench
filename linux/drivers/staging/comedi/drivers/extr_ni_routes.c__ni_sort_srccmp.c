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

__attribute__((used)) static int _ni_sort_srccmp(const void *vsrc0, const void *vsrc1)
{
	const int *src0 = vsrc0;
	const int *src1 = vsrc1;

	if (*src0 < *src1)
		return -1;
	else if (*src0 > *src1)
		return 1;
	return 0;
}