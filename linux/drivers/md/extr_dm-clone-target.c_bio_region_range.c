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
struct clone {unsigned long region_shift; int /*<<< orphan*/  region_size; } ;
struct TYPE_2__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {TYPE_1__ bi_iter; } ;

/* Variables and functions */
 unsigned long bio_end_sector (struct bio*) ; 
 unsigned long dm_sector_div_up (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bio_region_range(struct clone *clone, struct bio *bio,
			     unsigned long *rs, unsigned long *re)
{
	*rs = dm_sector_div_up(bio->bi_iter.bi_sector, clone->region_size);
	*re = bio_end_sector(bio) >> clone->region_shift;
}