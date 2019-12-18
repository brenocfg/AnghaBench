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
struct pblk_gc {int /*<<< orphan*/  gc_active; scalar_t__ gc_enabled; } ;
struct pblk {struct pblk_gc gc; } ;

/* Variables and functions */
 int /*<<< orphan*/  pblk_gc_kick (struct pblk*) ; 
 int /*<<< orphan*/  pblk_gc_start (struct pblk*) ; 

void pblk_gc_should_start(struct pblk *pblk)
{
	struct pblk_gc *gc = &pblk->gc;

	if (gc->gc_enabled && !gc->gc_active) {
		pblk_gc_start(pblk);
		pblk_gc_kick(pblk);
	}
}