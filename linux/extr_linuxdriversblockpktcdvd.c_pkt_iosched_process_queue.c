#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pending_bios; } ;
struct TYPE_5__ {int writing; scalar_t__ last_write; scalar_t__ successive_reads; int /*<<< orphan*/  lock; int /*<<< orphan*/  read_queue; int /*<<< orphan*/  write_queue; int /*<<< orphan*/  attention; } ;
struct pktcdvd_device {scalar_t__ read_speed; scalar_t__ write_speed; TYPE_3__ cdrw; TYPE_2__ iosched; } ;
struct TYPE_4__ {scalar_t__ bi_sector; int bi_size; } ;
struct bio {TYPE_1__ bi_iter; } ;

/* Variables and functions */
 scalar_t__ HI_SPEED_SWITCH ; 
 scalar_t__ MAX_SPEED ; 
 scalar_t__ READ ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 scalar_t__ bio_end_sector (struct bio*) ; 
 int /*<<< orphan*/  bio_list_empty (int /*<<< orphan*/ *) ; 
 struct bio* bio_list_peek (int /*<<< orphan*/ *) ; 
 struct bio* bio_list_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 int /*<<< orphan*/  pkt_dbg (int,struct pktcdvd_device*,char*) ; 
 int /*<<< orphan*/  pkt_flush_cache (struct pktcdvd_device*) ; 
 int /*<<< orphan*/  pkt_set_speed (struct pktcdvd_device*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pkt_iosched_process_queue(struct pktcdvd_device *pd)
{

	if (atomic_read(&pd->iosched.attention) == 0)
		return;
	atomic_set(&pd->iosched.attention, 0);

	for (;;) {
		struct bio *bio;
		int reads_queued, writes_queued;

		spin_lock(&pd->iosched.lock);
		reads_queued = !bio_list_empty(&pd->iosched.read_queue);
		writes_queued = !bio_list_empty(&pd->iosched.write_queue);
		spin_unlock(&pd->iosched.lock);

		if (!reads_queued && !writes_queued)
			break;

		if (pd->iosched.writing) {
			int need_write_seek = 1;
			spin_lock(&pd->iosched.lock);
			bio = bio_list_peek(&pd->iosched.write_queue);
			spin_unlock(&pd->iosched.lock);
			if (bio && (bio->bi_iter.bi_sector ==
				    pd->iosched.last_write))
				need_write_seek = 0;
			if (need_write_seek && reads_queued) {
				if (atomic_read(&pd->cdrw.pending_bios) > 0) {
					pkt_dbg(2, pd, "write, waiting\n");
					break;
				}
				pkt_flush_cache(pd);
				pd->iosched.writing = 0;
			}
		} else {
			if (!reads_queued && writes_queued) {
				if (atomic_read(&pd->cdrw.pending_bios) > 0) {
					pkt_dbg(2, pd, "read, waiting\n");
					break;
				}
				pd->iosched.writing = 1;
			}
		}

		spin_lock(&pd->iosched.lock);
		if (pd->iosched.writing)
			bio = bio_list_pop(&pd->iosched.write_queue);
		else
			bio = bio_list_pop(&pd->iosched.read_queue);
		spin_unlock(&pd->iosched.lock);

		if (!bio)
			continue;

		if (bio_data_dir(bio) == READ)
			pd->iosched.successive_reads +=
				bio->bi_iter.bi_size >> 10;
		else {
			pd->iosched.successive_reads = 0;
			pd->iosched.last_write = bio_end_sector(bio);
		}
		if (pd->iosched.successive_reads >= HI_SPEED_SWITCH) {
			if (pd->read_speed == pd->write_speed) {
				pd->read_speed = MAX_SPEED;
				pkt_set_speed(pd, pd->write_speed, pd->read_speed);
			}
		} else {
			if (pd->read_speed != pd->write_speed) {
				pd->read_speed = pd->write_speed;
				pkt_set_speed(pd, pd->write_speed, pd->read_speed);
			}
		}

		atomic_inc(&pd->cdrw.pending_bios);
		generic_make_request(bio);
	}
}