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
struct list_head {int dummy; } ;
struct dm_origin {int /*<<< orphan*/  hash_list; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 struct list_head* _dm_origins ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 size_t origin_hash (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __insert_dm_origin(struct dm_origin *o)
{
	struct list_head *sl = &_dm_origins[origin_hash(o->dev->bdev)];
	list_add_tail(&o->hash_list, sl);
}