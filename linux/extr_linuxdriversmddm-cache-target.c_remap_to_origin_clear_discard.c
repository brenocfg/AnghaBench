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
typedef  int /*<<< orphan*/  dm_oblock_t ;

/* Variables and functions */
 int /*<<< orphan*/  __remap_to_origin_clear_discard (struct cache*,struct bio*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void remap_to_origin_clear_discard(struct cache *cache, struct bio *bio,
					  dm_oblock_t oblock)
{
	// FIXME: check_if_tick_bio_needed() is called way too much through this interface
	__remap_to_origin_clear_discard(cache, bio, oblock, true);
}