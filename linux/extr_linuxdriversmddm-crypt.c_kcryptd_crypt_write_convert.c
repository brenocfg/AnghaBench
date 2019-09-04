#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cc_pending; int /*<<< orphan*/  iter_out; struct bio* bio_out; } ;
struct dm_crypt_io {int /*<<< orphan*/  sector; TYPE_2__ ctx; scalar_t__ error; TYPE_3__* base_bio; struct crypt_config* cc; } ;
struct crypt_config {int dummy; } ;
struct bio {int /*<<< orphan*/  bi_iter; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  scalar_t__ blk_status_t ;
struct TYPE_5__ {int /*<<< orphan*/  bi_size; } ;
struct TYPE_7__ {TYPE_1__ bi_iter; } ;

/* Variables and functions */
 scalar_t__ BLK_STS_IOERR ; 
 int atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ bio_sectors (struct bio*) ; 
 struct bio* crypt_alloc_buffer (struct dm_crypt_io*,int /*<<< orphan*/ ) ; 
 scalar_t__ crypt_convert (struct crypt_config*,TYPE_2__*) ; 
 int /*<<< orphan*/  crypt_convert_init (struct crypt_config*,TYPE_2__*,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypt_dec_pending (struct dm_crypt_io*) ; 
 int /*<<< orphan*/  crypt_inc_pending (struct dm_crypt_io*) ; 
 int /*<<< orphan*/  kcryptd_crypt_write_io_submit (struct dm_crypt_io*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void kcryptd_crypt_write_convert(struct dm_crypt_io *io)
{
	struct crypt_config *cc = io->cc;
	struct bio *clone;
	int crypt_finished;
	sector_t sector = io->sector;
	blk_status_t r;

	/*
	 * Prevent io from disappearing until this function completes.
	 */
	crypt_inc_pending(io);
	crypt_convert_init(cc, &io->ctx, NULL, io->base_bio, sector);

	clone = crypt_alloc_buffer(io, io->base_bio->bi_iter.bi_size);
	if (unlikely(!clone)) {
		io->error = BLK_STS_IOERR;
		goto dec;
	}

	io->ctx.bio_out = clone;
	io->ctx.iter_out = clone->bi_iter;

	sector += bio_sectors(clone);

	crypt_inc_pending(io);
	r = crypt_convert(cc, &io->ctx);
	if (r)
		io->error = r;
	crypt_finished = atomic_dec_and_test(&io->ctx.cc_pending);

	/* Encryption was already finished, submit io now */
	if (crypt_finished) {
		kcryptd_crypt_write_io_submit(io, 0);
		io->sector = sector;
	}

dec:
	crypt_dec_pending(io);
}