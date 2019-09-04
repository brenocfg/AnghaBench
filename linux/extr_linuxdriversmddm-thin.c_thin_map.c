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
struct dm_target {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {TYPE_1__ bi_iter; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_target_offset (struct dm_target*,int /*<<< orphan*/ ) ; 
 int thin_bio_map (struct dm_target*,struct bio*) ; 

__attribute__((used)) static int thin_map(struct dm_target *ti, struct bio *bio)
{
	bio->bi_iter.bi_sector = dm_target_offset(ti, bio->bi_iter.bi_sector);

	return thin_bio_map(ti, bio);
}