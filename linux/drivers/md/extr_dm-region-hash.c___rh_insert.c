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
struct dm_region_hash {scalar_t__ buckets; } ;
struct dm_region {int /*<<< orphan*/  key; int /*<<< orphan*/  hash_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ rh_hash (struct dm_region_hash*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __rh_insert(struct dm_region_hash *rh, struct dm_region *reg)
{
	list_add(&reg->hash_list, rh->buckets + rh_hash(rh, reg->key));
}