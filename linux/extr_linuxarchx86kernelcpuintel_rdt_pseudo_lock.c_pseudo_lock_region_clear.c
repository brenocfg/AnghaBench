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
struct pseudo_lock_region {int /*<<< orphan*/ * debugfs_dir; scalar_t__ cbm; TYPE_1__* d; int /*<<< orphan*/ * r; int /*<<< orphan*/ * kmem; scalar_t__ line_size; scalar_t__ size; } ;
struct TYPE_2__ {int /*<<< orphan*/ * plr; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pseudo_lock_region_clear(struct pseudo_lock_region *plr)
{
	plr->size = 0;
	plr->line_size = 0;
	kfree(plr->kmem);
	plr->kmem = NULL;
	plr->r = NULL;
	if (plr->d)
		plr->d->plr = NULL;
	plr->d = NULL;
	plr->cbm = 0;
	plr->debugfs_dir = NULL;
}