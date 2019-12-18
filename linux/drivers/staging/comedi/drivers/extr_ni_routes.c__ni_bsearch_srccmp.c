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

__attribute__((used)) static int _ni_bsearch_srccmp(const void *vkey, const void *velt)
{
	const int *key = vkey;
	const int *elt = velt;

	if (*key < *elt)
		return -1;
	else if (*key > *elt)
		return 1;
	return 0;
}