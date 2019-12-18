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
struct hash_table_bucket {int dummy; } ;
struct dm_clone_region_hydration {int /*<<< orphan*/  region_nr; } ;

/* Variables and functions */
 struct dm_clone_region_hydration* __hash_find (struct hash_table_bucket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __insert_region_hydration (struct hash_table_bucket*,struct dm_clone_region_hydration*) ; 

__attribute__((used)) static struct dm_clone_region_hydration *
__find_or_insert_region_hydration(struct hash_table_bucket *bucket,
				  struct dm_clone_region_hydration *hd)
{
	struct dm_clone_region_hydration *hd2;

	hd2 = __hash_find(bucket, hd->region_nr);
	if (hd2)
		return hd2;

	__insert_region_hydration(bucket, hd);

	return hd;
}