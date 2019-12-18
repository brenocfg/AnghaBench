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
struct nfp_bar {scalar_t__ bitsize; int index; } ;

/* Variables and functions */

__attribute__((used)) static int bar_cmp(const void *aptr, const void *bptr)
{
	const struct nfp_bar *a = aptr, *b = bptr;

	if (a->bitsize == b->bitsize)
		return a->index - b->index;
	else
		return a->bitsize - b->bitsize;
}