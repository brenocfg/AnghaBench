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
struct mapped_device {int /*<<< orphan*/  bs; int /*<<< orphan*/  io_bs; } ;
struct dm_table {int dummy; } ;
struct dm_md_mempools {int /*<<< orphan*/  io_bs; int /*<<< orphan*/  bs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  bioset_exit (int /*<<< orphan*/ *) ; 
 int bioset_init_from_src (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bioset_initialized (int /*<<< orphan*/ *) ; 
 scalar_t__ dm_table_bio_based (struct dm_table*) ; 
 int /*<<< orphan*/  dm_table_free_md_mempools (struct dm_table*) ; 
 struct dm_md_mempools* dm_table_get_md_mempools (struct dm_table*) ; 

__attribute__((used)) static int __bind_mempools(struct mapped_device *md, struct dm_table *t)
{
	struct dm_md_mempools *p = dm_table_get_md_mempools(t);
	int ret = 0;

	if (dm_table_bio_based(t)) {
		/*
		 * The md may already have mempools that need changing.
		 * If so, reload bioset because front_pad may have changed
		 * because a different table was loaded.
		 */
		bioset_exit(&md->bs);
		bioset_exit(&md->io_bs);

	} else if (bioset_initialized(&md->bs)) {
		/*
		 * There's no need to reload with request-based dm
		 * because the size of front_pad doesn't change.
		 * Note for future: If you are to reload bioset,
		 * prep-ed requests in the queue may refer
		 * to bio from the old bioset, so you must walk
		 * through the queue to unprep.
		 */
		goto out;
	}

	BUG_ON(!p ||
	       bioset_initialized(&md->bs) ||
	       bioset_initialized(&md->io_bs));

	ret = bioset_init_from_src(&md->bs, &p->bs);
	if (ret)
		goto out;
	ret = bioset_init_from_src(&md->io_bs, &p->io_bs);
	if (ret)
		bioset_exit(&md->bs);
out:
	/* mempool bind completed, no longer need any mempools in the table */
	dm_table_free_md_mempools(t);
	return ret;
}