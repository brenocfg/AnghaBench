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
struct hash_table_bucket {int /*<<< orphan*/  head; } ;
struct dm_clone_region_hydration {int /*<<< orphan*/  h; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void __insert_region_hydration(struct hash_table_bucket *bucket,
					     struct dm_clone_region_hydration *hd)
{
	hlist_add_head(&hd->h, &bucket->head);
}