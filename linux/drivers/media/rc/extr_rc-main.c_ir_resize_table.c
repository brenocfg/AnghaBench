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
struct rc_map_table {int dummy; } ;
struct rc_map {unsigned int alloc; int size; int len; struct rc_map_table* scan; } ;
struct rc_dev {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned int IR_TAB_MAX_SIZE ; 
 unsigned int IR_TAB_MIN_SIZE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  kfree (struct rc_map_table*) ; 
 struct rc_map_table* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct rc_map_table*,struct rc_map_table*,int) ; 

__attribute__((used)) static int ir_resize_table(struct rc_dev *dev, struct rc_map *rc_map,
			   gfp_t gfp_flags)
{
	unsigned int oldalloc = rc_map->alloc;
	unsigned int newalloc = oldalloc;
	struct rc_map_table *oldscan = rc_map->scan;
	struct rc_map_table *newscan;

	if (rc_map->size == rc_map->len) {
		/* All entries in use -> grow keytable */
		if (rc_map->alloc >= IR_TAB_MAX_SIZE)
			return -ENOMEM;

		newalloc *= 2;
		dev_dbg(&dev->dev, "Growing table to %u bytes\n", newalloc);
	}

	if ((rc_map->len * 3 < rc_map->size) && (oldalloc > IR_TAB_MIN_SIZE)) {
		/* Less than 1/3 of entries in use -> shrink keytable */
		newalloc /= 2;
		dev_dbg(&dev->dev, "Shrinking table to %u bytes\n", newalloc);
	}

	if (newalloc == oldalloc)
		return 0;

	newscan = kmalloc(newalloc, gfp_flags);
	if (!newscan)
		return -ENOMEM;

	memcpy(newscan, rc_map->scan, rc_map->len * sizeof(struct rc_map_table));
	rc_map->scan = newscan;
	rc_map->alloc = newalloc;
	rc_map->size = rc_map->alloc / sizeof(struct rc_map_table);
	kfree(oldscan);
	return 0;
}