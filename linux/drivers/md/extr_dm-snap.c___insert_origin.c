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
struct origin {int /*<<< orphan*/  hash_list; int /*<<< orphan*/  bdev; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 struct list_head* _origins ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 size_t origin_hash (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __insert_origin(struct origin *o)
{
	struct list_head *sl = &_origins[origin_hash(o->bdev)];
	list_add_tail(&o->hash_list, sl);
}