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
struct resource {int flags; } ;

/* Variables and functions */
 int DPA_RESOURCE_ADJUSTED ; 

__attribute__((used)) static bool is_old_resource(struct resource *res, struct resource **list, int n)
{
	int i;

	if (res->flags & DPA_RESOURCE_ADJUSTED)
		return false;
	for (i = 0; i < n; i++)
		if (res == list[i])
			return true;
	return false;
}