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
struct TYPE_2__ {int /*<<< orphan*/  attention; int /*<<< orphan*/  lock; int /*<<< orphan*/  write_queue; int /*<<< orphan*/  read_queue; } ;
struct pktcdvd_device {int /*<<< orphan*/  wqueue; TYPE_1__ iosched; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 scalar_t__ READ ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  bio_list_add (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pkt_queue_bio(struct pktcdvd_device *pd, struct bio *bio)
{
	spin_lock(&pd->iosched.lock);
	if (bio_data_dir(bio) == READ)
		bio_list_add(&pd->iosched.read_queue, bio);
	else
		bio_list_add(&pd->iosched.write_queue, bio);
	spin_unlock(&pd->iosched.lock);

	atomic_set(&pd->iosched.attention, 1);
	wake_up(&pd->wqueue);
}