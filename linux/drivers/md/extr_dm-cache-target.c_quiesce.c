#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ws; } ;
struct dm_cache_migration {TYPE_2__ k; int /*<<< orphan*/  cell; TYPE_1__* cache; } ;
struct TYPE_3__ {int /*<<< orphan*/  prison; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_cell_quiesce_v2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_continuation (TYPE_2__*,void (*) (struct work_struct*)) ; 

__attribute__((used)) static void quiesce(struct dm_cache_migration *mg,
		    void (*continuation)(struct work_struct *))
{
	init_continuation(&mg->k, continuation);
	dm_cell_quiesce_v2(mg->cache->prison, mg->cell, &mg->k.ws);
}