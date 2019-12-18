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
struct mtd_info {struct map_info* priv; } ;
struct map_info {TYPE_1__* fldrv; } ;
struct TYPE_2__ {int /*<<< orphan*/  module; int /*<<< orphan*/  (* destroy ) (struct mtd_info*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mtd_info*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*) ; 

void map_destroy(struct mtd_info *mtd)
{
	struct map_info *map = mtd->priv;

	if (map->fldrv->destroy)
		map->fldrv->destroy(mtd);

	module_put(map->fldrv->module);

	kfree(mtd);
}