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
struct cache {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 scalar_t__ DM_MAPIO_REMAPPED ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 int /*<<< orphan*/  get_bio_block (struct cache*,struct bio*) ; 
 scalar_t__ map_bio (struct cache*,struct bio*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool process_bio(struct cache *cache, struct bio *bio)
{
	bool commit_needed;

	if (map_bio(cache, bio, get_bio_block(cache, bio), &commit_needed) == DM_MAPIO_REMAPPED)
		generic_make_request(bio);

	return commit_needed;
}