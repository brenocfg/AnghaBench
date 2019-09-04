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
struct mtd_info {int writesize; int /*<<< orphan*/  erasesize; scalar_t__ flags; int /*<<< orphan*/  _sync; int /*<<< orphan*/  _write; int /*<<< orphan*/  _read; int /*<<< orphan*/  _erase; int /*<<< orphan*/  size; int /*<<< orphan*/  type; int /*<<< orphan*/  name; struct map_info* priv; } ;
struct map_info {int /*<<< orphan*/  size; int /*<<< orphan*/  name; int /*<<< orphan*/ * fldrv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MTD_ABSENT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 struct mtd_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_absent_chipdrv ; 
 int /*<<< orphan*/  map_absent_erase ; 
 int /*<<< orphan*/  map_absent_read ; 
 int /*<<< orphan*/  map_absent_sync ; 
 int /*<<< orphan*/  map_absent_write ; 

__attribute__((used)) static struct mtd_info *map_absent_probe(struct map_info *map)
{
	struct mtd_info *mtd;

	mtd = kzalloc(sizeof(*mtd), GFP_KERNEL);
	if (!mtd) {
		return NULL;
	}

	map->fldrv 	= &map_absent_chipdrv;
	mtd->priv 	= map;
	mtd->name 	= map->name;
	mtd->type 	= MTD_ABSENT;
	mtd->size 	= map->size;
	mtd->_erase 	= map_absent_erase;
	mtd->_read 	= map_absent_read;
	mtd->_write 	= map_absent_write;
	mtd->_sync 	= map_absent_sync;
	mtd->flags 	= 0;
	mtd->erasesize  = PAGE_SIZE;
	mtd->writesize  = 1;

	__module_get(THIS_MODULE);
	return mtd;
}