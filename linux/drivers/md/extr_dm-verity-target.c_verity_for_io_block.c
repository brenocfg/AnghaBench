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
struct scatterlist {int dummy; } ;
struct dm_verity_io {int dummy; } ;
struct dm_verity {int data_dev_block_bits; TYPE_1__* ti; } ;
struct crypto_wait {int dummy; } ;
struct bvec_iter {int dummy; } ;
struct bio_vec {unsigned int bv_len; int /*<<< orphan*/  bv_offset; int /*<<< orphan*/  bv_page; } ;
struct bio {int dummy; } ;
struct ahash_request {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  per_io_data_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,int) ; 
 int /*<<< orphan*/  ahash_request_set_crypt (struct ahash_request*,struct scatterlist*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  bio_advance_iter (struct bio*,struct bvec_iter*,unsigned int) ; 
 struct bio_vec bio_iter_iovec (struct bio*,struct bvec_iter) ; 
 int /*<<< orphan*/  crypto_ahash_update (struct ahash_request*) ; 
 int crypto_wait_req (int /*<<< orphan*/ ,struct crypto_wait*) ; 
 struct bio* dm_bio_from_per_bio_data (struct dm_verity_io*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 struct ahash_request* verity_io_hash_req (struct dm_verity*,struct dm_verity_io*) ; 

__attribute__((used)) static int verity_for_io_block(struct dm_verity *v, struct dm_verity_io *io,
			       struct bvec_iter *iter, struct crypto_wait *wait)
{
	unsigned int todo = 1 << v->data_dev_block_bits;
	struct bio *bio = dm_bio_from_per_bio_data(io, v->ti->per_io_data_size);
	struct scatterlist sg;
	struct ahash_request *req = verity_io_hash_req(v, io);

	do {
		int r;
		unsigned int len;
		struct bio_vec bv = bio_iter_iovec(bio, *iter);

		sg_init_table(&sg, 1);

		len = bv.bv_len;

		if (likely(len >= todo))
			len = todo;
		/*
		 * Operating on a single page at a time looks suboptimal
		 * until you consider the typical block size is 4,096B.
		 * Going through this loops twice should be very rare.
		 */
		sg_set_page(&sg, bv.bv_page, len, bv.bv_offset);
		ahash_request_set_crypt(req, &sg, NULL, len);
		r = crypto_wait_req(crypto_ahash_update(req), wait);

		if (unlikely(r < 0)) {
			DMERR("verity_for_io_block crypto op failed: %d", r);
			return r;
		}

		bio_advance_iter(bio, iter, len);
		todo -= len;
	} while (todo);

	return 0;
}