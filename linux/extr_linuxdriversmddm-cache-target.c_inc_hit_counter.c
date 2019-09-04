#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  write_hit; int /*<<< orphan*/  read_hit; } ;
struct cache {TYPE_1__ stats; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 scalar_t__ READ ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ bio_data_dir (struct bio*) ; 

__attribute__((used)) static void inc_hit_counter(struct cache *cache, struct bio *bio)
{
	atomic_inc(bio_data_dir(bio) == READ ?
		   &cache->stats.read_hit : &cache->stats.write_hit);
}