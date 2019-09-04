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
typedef  int /*<<< orphan*/  u64 ;
struct rc_map_table {int dummy; } ;
struct rc_map {int alloc; int size; int /*<<< orphan*/ * name; int /*<<< orphan*/  scan; int /*<<< orphan*/  rc_proto; } ;
struct rc_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kstrdup (char const*,int /*<<< orphan*/ ) ; 
 int roundup_pow_of_two (size_t) ; 

__attribute__((used)) static int ir_create_table(struct rc_dev *dev, struct rc_map *rc_map,
			   const char *name, u64 rc_proto, size_t size)
{
	rc_map->name = kstrdup(name, GFP_KERNEL);
	if (!rc_map->name)
		return -ENOMEM;
	rc_map->rc_proto = rc_proto;
	rc_map->alloc = roundup_pow_of_two(size * sizeof(struct rc_map_table));
	rc_map->size = rc_map->alloc / sizeof(struct rc_map_table);
	rc_map->scan = kmalloc(rc_map->alloc, GFP_KERNEL);
	if (!rc_map->scan) {
		kfree(rc_map->name);
		rc_map->name = NULL;
		return -ENOMEM;
	}

	dev_dbg(&dev->dev, "Allocated space for %u keycode entries (%u bytes)\n",
		rc_map->size, rc_map->alloc);
	return 0;
}