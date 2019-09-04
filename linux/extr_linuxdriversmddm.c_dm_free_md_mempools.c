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
struct dm_md_mempools {int /*<<< orphan*/  io_bs; int /*<<< orphan*/  bs; } ;

/* Variables and functions */
 int /*<<< orphan*/  bioset_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dm_md_mempools*) ; 

void dm_free_md_mempools(struct dm_md_mempools *pools)
{
	if (!pools)
		return;

	bioset_exit(&pools->bs);
	bioset_exit(&pools->io_bs);

	kfree(pools);
}