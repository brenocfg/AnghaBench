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
struct per_bio_data {int /*<<< orphan*/  len; } ;
struct cache {int /*<<< orphan*/  tracker; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 scalar_t__ accountable_bio (struct cache*,struct bio*) ; 
 int /*<<< orphan*/  bio_sectors (struct bio*) ; 
 struct per_bio_data* get_per_bio_data (struct bio*) ; 
 int /*<<< orphan*/  iot_io_begin (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void accounted_begin(struct cache *cache, struct bio *bio)
{
	struct per_bio_data *pb;

	if (accountable_bio(cache, bio)) {
		pb = get_per_bio_data(bio);
		pb->len = bio_sectors(bio);
		iot_io_begin(&cache->tracker, pb->len);
	}
}