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
struct pblk_gc {scalar_t__ gc_active; int /*<<< orphan*/  gc_forced; } ;
struct pblk {struct pblk_gc gc; } ;

/* Variables and functions */

void pblk_gc_should_stop(struct pblk *pblk)
{
	struct pblk_gc *gc = &pblk->gc;

	if (gc->gc_active && !gc->gc_forced)
		gc->gc_active = 0;
}