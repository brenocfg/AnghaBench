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
struct mtd_info {int size; int writesize; int erasesize; int /*<<< orphan*/  flags; int /*<<< orphan*/  _unpoint; int /*<<< orphan*/  _sync; int /*<<< orphan*/  _point; void* _panic_write; void* _write; int /*<<< orphan*/  _read; int /*<<< orphan*/  _erase; int /*<<< orphan*/  type; int /*<<< orphan*/  name; struct map_info* priv; } ;
struct map_info {int size; int /*<<< orphan*/  name; int /*<<< orphan*/ * fldrv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MTD_CAP_RAM ; 
 int /*<<< orphan*/  MTD_RAM ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 struct mtd_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int map_read8 (struct map_info*,int) ; 
 int /*<<< orphan*/  map_write8 (struct map_info*,int,int) ; 
 int /*<<< orphan*/  mapram_chipdrv ; 
 int /*<<< orphan*/  mapram_erase ; 
 int /*<<< orphan*/  mapram_nop ; 
 int /*<<< orphan*/  mapram_point ; 
 int /*<<< orphan*/  mapram_read ; 
 int /*<<< orphan*/  mapram_unpoint ; 
 void* mapram_write ; 

__attribute__((used)) static struct mtd_info *map_ram_probe(struct map_info *map)
{
	struct mtd_info *mtd;

	/* Check the first byte is RAM */
#if 0
	map_write8(map, 0x55, 0);
	if (map_read8(map, 0) != 0x55)
		return NULL;

	map_write8(map, 0xAA, 0);
	if (map_read8(map, 0) != 0xAA)
		return NULL;

	/* Check the last byte is RAM */
	map_write8(map, 0x55, map->size-1);
	if (map_read8(map, map->size-1) != 0x55)
		return NULL;

	map_write8(map, 0xAA, map->size-1);
	if (map_read8(map, map->size-1) != 0xAA)
		return NULL;
#endif
	/* OK. It seems to be RAM. */

	mtd = kzalloc(sizeof(*mtd), GFP_KERNEL);
	if (!mtd)
		return NULL;

	map->fldrv = &mapram_chipdrv;
	mtd->priv = map;
	mtd->name = map->name;
	mtd->type = MTD_RAM;
	mtd->size = map->size;
	mtd->_erase = mapram_erase;
	mtd->_read = mapram_read;
	mtd->_write = mapram_write;
	mtd->_panic_write = mapram_write;
	mtd->_point = mapram_point;
	mtd->_sync = mapram_nop;
	mtd->_unpoint = mapram_unpoint;
	mtd->flags = MTD_CAP_RAM;
	mtd->writesize = 1;

	mtd->erasesize = PAGE_SIZE;
 	while(mtd->size & (mtd->erasesize - 1))
		mtd->erasesize >>= 1;

	__module_get(THIS_MODULE);
	return mtd;
}