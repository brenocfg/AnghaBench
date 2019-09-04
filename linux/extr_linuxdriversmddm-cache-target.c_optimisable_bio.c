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
 scalar_t__ bio_writes_complete_block (struct cache*,struct bio*) ; 
 scalar_t__ is_discarded_oblock (struct cache*,int /*<<< orphan*/ ) ; 
 scalar_t__ writeback_mode (struct cache*) ; 

__attribute__((used)) static bool optimisable_bio(struct cache *cache, struct bio *bio, dm_oblock_t block)
{
	return writeback_mode(cache) &&
		(is_discarded_oblock(cache, block) || bio_writes_complete_block(cache, bio));
}