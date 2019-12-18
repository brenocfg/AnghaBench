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
struct dm_clone_region_hydration {scalar_t__ status; int /*<<< orphan*/  h; int /*<<< orphan*/  region_nr; struct clone* clone; } ;
struct clone {int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 scalar_t__ BLK_STS_OK ; 
 scalar_t__ CM_READ_ONLY ; 
 int EPERM ; 
 int /*<<< orphan*/  bucket_lock_irqsave (struct hash_table_bucket*,unsigned long) ; 
 int /*<<< orphan*/  bucket_unlock_irqrestore (struct hash_table_bucket*,unsigned long) ; 
 int dm_clone_set_region_hydrated (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_clone_mode (struct clone*) ; 
 struct hash_table_bucket* get_hash_table_bucket (struct clone*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int hydration_update_metadata(struct dm_clone_region_hydration *hd)
{
	int r = 0;
	unsigned long flags;
	struct hash_table_bucket *bucket;
	struct clone *clone = hd->clone;

	if (unlikely(get_clone_mode(clone) >= CM_READ_ONLY))
		r = -EPERM;

	/* Update the metadata */
	if (likely(!r) && hd->status == BLK_STS_OK)
		r = dm_clone_set_region_hydrated(clone->cmd, hd->region_nr);

	bucket = get_hash_table_bucket(clone, hd->region_nr);

	/* Remove hydration from hash table */
	bucket_lock_irqsave(bucket, flags);
	hlist_del(&hd->h);
	bucket_unlock_irqrestore(bucket, flags);

	return r;
}