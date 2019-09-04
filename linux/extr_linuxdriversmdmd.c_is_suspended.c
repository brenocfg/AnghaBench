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
struct mddev {scalar_t__ suspend_lo; scalar_t__ suspend_hi; scalar_t__ suspended; } ;
struct TYPE_2__ {scalar_t__ bi_sector; } ;
struct bio {TYPE_1__ bi_iter; } ;

/* Variables and functions */
 scalar_t__ WRITE ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 scalar_t__ bio_end_sector (struct bio*) ; 

__attribute__((used)) static bool is_suspended(struct mddev *mddev, struct bio *bio)
{
	if (mddev->suspended)
		return true;
	if (bio_data_dir(bio) != WRITE)
		return false;
	if (mddev->suspend_lo >= mddev->suspend_hi)
		return false;
	if (bio->bi_iter.bi_sector >= mddev->suspend_hi)
		return false;
	if (bio_end_sector(bio) < mddev->suspend_lo)
		return false;
	return true;
}