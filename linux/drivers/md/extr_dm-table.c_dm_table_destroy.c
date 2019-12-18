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
struct dm_target {TYPE_1__* type; } ;
struct dm_table {int depth; unsigned int num_targets; int /*<<< orphan*/  mempools; int /*<<< orphan*/  md; int /*<<< orphan*/  devices; int /*<<< orphan*/  highs; struct dm_target* targets; int /*<<< orphan*/ * index; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dtr ) (struct dm_target*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dm_free_md_mempools (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_put_target_type (TYPE_1__*) ; 
 int /*<<< orphan*/  free_devices (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dm_table*) ; 
 int /*<<< orphan*/  stub1 (struct dm_target*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

void dm_table_destroy(struct dm_table *t)
{
	unsigned int i;

	if (!t)
		return;

	/* free the indexes */
	if (t->depth >= 2)
		vfree(t->index[t->depth - 2]);

	/* free the targets */
	for (i = 0; i < t->num_targets; i++) {
		struct dm_target *tgt = t->targets + i;

		if (tgt->type->dtr)
			tgt->type->dtr(tgt);

		dm_put_target_type(tgt->type);
	}

	vfree(t->highs);

	/* free the device list */
	free_devices(&t->devices, t->md);

	dm_free_md_mempools(t->mempools);

	kfree(t);
}