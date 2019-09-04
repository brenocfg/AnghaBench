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
struct r1bio {int /*<<< orphan*/  sector; struct mddev* mddev; scalar_t__ state; int /*<<< orphan*/  sectors; struct bio* master_bio; } ;
struct mddev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {TYPE_1__ bi_iter; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_sectors (struct bio*) ; 

__attribute__((used)) static void init_r1bio(struct r1bio *r1_bio, struct mddev *mddev, struct bio *bio)
{
	r1_bio->master_bio = bio;
	r1_bio->sectors = bio_sectors(bio);
	r1_bio->state = 0;
	r1_bio->mddev = mddev;
	r1_bio->sector = bio->bi_iter.bi_sector;
}