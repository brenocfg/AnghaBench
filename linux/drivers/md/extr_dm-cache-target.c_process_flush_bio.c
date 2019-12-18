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
struct per_bio_data {int /*<<< orphan*/  req_nr; } ;
struct cache {int /*<<< orphan*/  committer; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 struct per_bio_data* get_per_bio_data (struct bio*) ; 
 int /*<<< orphan*/  issue_after_commit (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  remap_to_cache (struct cache*,struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remap_to_origin (struct cache*,struct bio*) ; 

__attribute__((used)) static bool process_flush_bio(struct cache *cache, struct bio *bio)
{
	struct per_bio_data *pb = get_per_bio_data(bio);

	if (!pb->req_nr)
		remap_to_origin(cache, bio);
	else
		remap_to_cache(cache, bio, 0);

	issue_after_commit(&cache->committer, bio);
	return true;
}