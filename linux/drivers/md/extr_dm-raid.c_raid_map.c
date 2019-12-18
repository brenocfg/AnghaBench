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
struct mddev {scalar_t__ array_sectors; } ;
struct raid_set {struct mddev md; } ;
struct dm_target {struct raid_set* private; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int DM_MAPIO_REQUEUE ; 
 int DM_MAPIO_SUBMITTED ; 
 scalar_t__ bio_end_sector (struct bio*) ; 
 int /*<<< orphan*/  md_handle_request (struct mddev*,struct bio*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int raid_map(struct dm_target *ti, struct bio *bio)
{
	struct raid_set *rs = ti->private;
	struct mddev *mddev = &rs->md;

	/*
	 * If we're reshaping to add disk(s)), ti->len and
	 * mddev->array_sectors will differ during the process
	 * (ti->len > mddev->array_sectors), so we have to requeue
	 * bios with addresses > mddev->array_sectors here or
	 * there will occur accesses past EOD of the component
	 * data images thus erroring the raid set.
	 */
	if (unlikely(bio_end_sector(bio) > mddev->array_sectors))
		return DM_MAPIO_REQUEUE;

	md_handle_request(mddev, bio);

	return DM_MAPIO_SUBMITTED;
}