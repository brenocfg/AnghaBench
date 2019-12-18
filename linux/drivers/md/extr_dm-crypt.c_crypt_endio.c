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
struct dm_crypt_io {scalar_t__ error; struct crypt_config* cc; } ;
struct crypt_config {int dummy; } ;
struct bio {scalar_t__ bi_status; struct dm_crypt_io* bi_private; } ;
typedef  scalar_t__ blk_status_t ;

/* Variables and functions */
 unsigned int READ ; 
 unsigned int WRITE ; 
 unsigned int bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  crypt_dec_pending (struct dm_crypt_io*) ; 
 int /*<<< orphan*/  crypt_free_buffer_pages (struct crypt_config*,struct bio*) ; 
 int /*<<< orphan*/  kcryptd_queue_crypt (struct dm_crypt_io*) ; 
 scalar_t__ unlikely (scalar_t__) ; 

__attribute__((used)) static void crypt_endio(struct bio *clone)
{
	struct dm_crypt_io *io = clone->bi_private;
	struct crypt_config *cc = io->cc;
	unsigned rw = bio_data_dir(clone);
	blk_status_t error;

	/*
	 * free the processed pages
	 */
	if (rw == WRITE)
		crypt_free_buffer_pages(cc, clone);

	error = clone->bi_status;
	bio_put(clone);

	if (rw == READ && !error) {
		kcryptd_queue_crypt(io);
		return;
	}

	if (unlikely(error))
		io->error = error;

	crypt_dec_pending(io);
}