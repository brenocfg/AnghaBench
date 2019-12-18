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
struct r10conf {scalar_t__ reshape_progress; int /*<<< orphan*/  wait_barrier; int /*<<< orphan*/  mddev; } ;
struct mddev {int /*<<< orphan*/  recovery; } ;
struct TYPE_2__ {scalar_t__ bi_sector; } ;
struct bio {TYPE_1__ bi_iter; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  MD_RECOVERY_RESHAPE ; 
 int /*<<< orphan*/  allow_barrier (struct r10conf*) ; 
 int /*<<< orphan*/  raid10_log (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_barrier (struct r10conf*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void regular_request_wait(struct mddev *mddev, struct r10conf *conf,
				 struct bio *bio, sector_t sectors)
{
	wait_barrier(conf);
	while (test_bit(MD_RECOVERY_RESHAPE, &mddev->recovery) &&
	    bio->bi_iter.bi_sector < conf->reshape_progress &&
	    bio->bi_iter.bi_sector + sectors > conf->reshape_progress) {
		raid10_log(conf->mddev, "wait reshape");
		allow_barrier(conf);
		wait_event(conf->wait_barrier,
			   conf->reshape_progress <= bio->bi_iter.bi_sector ||
			   conf->reshape_progress >= bio->bi_iter.bi_sector +
			   sectors);
		wait_barrier(conf);
	}
}