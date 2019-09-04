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
struct dmz_mblock {int /*<<< orphan*/  state; } ;
struct bio {scalar_t__ bi_status; struct dmz_mblock* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMZ_META_ERROR ; 
 int DMZ_META_READING ; 
 int DMZ_META_WRITING ; 
 scalar_t__ REQ_OP_WRITE ; 
 scalar_t__ bio_op (struct bio*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  clear_bit_unlock (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void dmz_mblock_bio_end_io(struct bio *bio)
{
	struct dmz_mblock *mblk = bio->bi_private;
	int flag;

	if (bio->bi_status)
		set_bit(DMZ_META_ERROR, &mblk->state);

	if (bio_op(bio) == REQ_OP_WRITE)
		flag = DMZ_META_WRITING;
	else
		flag = DMZ_META_READING;

	clear_bit_unlock(flag, &mblk->state);
	smp_mb__after_atomic();
	wake_up_bit(&mblk->state, flag);

	bio_put(bio);
}