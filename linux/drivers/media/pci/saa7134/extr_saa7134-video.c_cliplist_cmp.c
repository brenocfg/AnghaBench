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
struct cliplist {scalar_t__ position; } ;

/* Variables and functions */

__attribute__((used)) static int cliplist_cmp(const void *a, const void *b)
{
	const struct cliplist *cla = a;
	const struct cliplist *clb = b;
	if (cla->position < clb->position)
		return -1;
	if (cla->position > clb->position)
		return 1;
	return 0;
}