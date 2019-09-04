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
struct switch_ctx {size_t nr_paths; int /*<<< orphan*/  region_table; TYPE_1__* path_list; } ;
struct dm_target {struct switch_ctx* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  dmdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_put_device (struct dm_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct switch_ctx*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void switch_dtr(struct dm_target *ti)
{
	struct switch_ctx *sctx = ti->private;

	while (sctx->nr_paths--)
		dm_put_device(ti, sctx->path_list[sctx->nr_paths].dmdev);

	vfree(sctx->region_table);
	kfree(sctx);
}