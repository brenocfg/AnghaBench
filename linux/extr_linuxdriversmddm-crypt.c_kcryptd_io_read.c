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
struct dm_crypt_io {scalar_t__ sector; int /*<<< orphan*/  base_bio; struct crypt_config* cc; } ;
struct crypt_config {scalar_t__ start; int /*<<< orphan*/  bs; } ;
struct TYPE_2__ {scalar_t__ bi_sector; } ;
struct bio {TYPE_1__ bi_iter; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct bio* bio_clone_fast (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  clone_init (struct dm_crypt_io*,struct bio*) ; 
 int /*<<< orphan*/  crypt_dec_pending (struct dm_crypt_io*) ; 
 int /*<<< orphan*/  crypt_inc_pending (struct dm_crypt_io*) ; 
 scalar_t__ dm_crypt_integrity_io_alloc (struct dm_crypt_io*,struct bio*) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 

__attribute__((used)) static int kcryptd_io_read(struct dm_crypt_io *io, gfp_t gfp)
{
	struct crypt_config *cc = io->cc;
	struct bio *clone;

	/*
	 * We need the original biovec array in order to decrypt
	 * the whole bio data *afterwards* -- thanks to immutable
	 * biovecs we don't need to worry about the block layer
	 * modifying the biovec array; so leverage bio_clone_fast().
	 */
	clone = bio_clone_fast(io->base_bio, gfp, &cc->bs);
	if (!clone)
		return 1;

	crypt_inc_pending(io);

	clone_init(io, clone);
	clone->bi_iter.bi_sector = cc->start + io->sector;

	if (dm_crypt_integrity_io_alloc(io, clone)) {
		crypt_dec_pending(io);
		bio_put(clone);
		return 1;
	}

	generic_make_request(clone);
	return 0;
}