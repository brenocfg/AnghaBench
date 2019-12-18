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
struct dm_clone_region_hydration {struct clone* clone; } ;
struct clone {int /*<<< orphan*/  hydration_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 struct dm_clone_region_hydration* mempool_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dm_clone_region_hydration *alloc_hydration(struct clone *clone)
{
	struct dm_clone_region_hydration *hd;

	/*
	 * Allocate a hydration from the hydration mempool.
	 * This might block but it can't fail.
	 */
	hd = mempool_alloc(&clone->hydration_pool, GFP_NOIO);
	hd->clone = clone;

	return hd;
}