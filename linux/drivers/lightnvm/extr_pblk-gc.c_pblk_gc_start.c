#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int gc_active; } ;
struct pblk {TYPE_1__ gc; } ;

/* Variables and functions */
 int /*<<< orphan*/  pblk_debug (struct pblk*,char*) ; 

__attribute__((used)) static void pblk_gc_start(struct pblk *pblk)
{
	pblk->gc.gc_active = 1;
	pblk_debug(pblk, "gc start\n");
}