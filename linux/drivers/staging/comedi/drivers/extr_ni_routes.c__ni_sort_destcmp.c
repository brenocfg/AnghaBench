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
struct ni_route_set {scalar_t__ dest; } ;

/* Variables and functions */

__attribute__((used)) static int _ni_sort_destcmp(const void *va, const void *vb)
{
	const struct ni_route_set *a = va;
	const struct ni_route_set *b = vb;

	if (a->dest < b->dest)
		return -1;
	else if (a->dest > b->dest)
		return 1;
	return 0;
}