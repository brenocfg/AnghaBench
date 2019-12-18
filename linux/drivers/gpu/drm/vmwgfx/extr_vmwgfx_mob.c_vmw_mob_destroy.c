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
struct vmw_mob {int /*<<< orphan*/ * pt_bo; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct vmw_mob*) ; 
 int /*<<< orphan*/  ttm_bo_put (int /*<<< orphan*/ *) ; 

void vmw_mob_destroy(struct vmw_mob *mob)
{
	if (mob->pt_bo) {
		ttm_bo_put(mob->pt_bo);
		mob->pt_bo = NULL;
	}
	kfree(mob);
}