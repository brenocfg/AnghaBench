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
struct ubi_wl_entry {int dummy; } ;
struct ubi_fm_pool {int used; int size; size_t* pebs; } ;
struct ubi_device {int /*<<< orphan*/  free_count; int /*<<< orphan*/  free; struct ubi_wl_entry** lookuptbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  wl_tree_add (struct ubi_wl_entry*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void return_unused_pool_pebs(struct ubi_device *ubi,
				    struct ubi_fm_pool *pool)
{
	int i;
	struct ubi_wl_entry *e;

	for (i = pool->used; i < pool->size; i++) {
		e = ubi->lookuptbl[pool->pebs[i]];
		wl_tree_add(e, &ubi->free);
		ubi->free_count++;
	}
}