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
 int memord (void const*,size_t,void const*,size_t) ; 

__attribute__((used)) static int ev_uniq_ord(const void *v1, size_t s1, unsigned d1, const void *v2,
		       size_t s2, unsigned d2)
{
	int r = memord(v1, s1, v2, s2);

	if (r)
		return r;
	if (d1 > d2)
		return 1;
	if (d2 > d1)
		return -1;
	return 0;
}