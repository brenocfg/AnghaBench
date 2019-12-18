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
struct dm_clone_region_hydration {TYPE_1__* clone; } ;
struct TYPE_2__ {int /*<<< orphan*/  hydration_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  mempool_free (struct dm_clone_region_hydration*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void free_hydration(struct dm_clone_region_hydration *hd)
{
	mempool_free(hd, &hd->clone->hydration_pool);
}