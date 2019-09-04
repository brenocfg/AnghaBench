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
struct drbd_device {int dummy; } ;
struct bio_and_error {TYPE_1__* bio; int /*<<< orphan*/  error; } ;
struct TYPE_2__ {int /*<<< orphan*/  bi_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_endio (TYPE_1__*) ; 
 int /*<<< orphan*/  dec_ap_bio (struct drbd_device*) ; 
 int /*<<< orphan*/  errno_to_blk_status (int /*<<< orphan*/ ) ; 

void complete_master_bio(struct drbd_device *device,
		struct bio_and_error *m)
{
	m->bio->bi_status = errno_to_blk_status(m->error);
	bio_endio(m->bio);
	dec_ap_bio(device);
}