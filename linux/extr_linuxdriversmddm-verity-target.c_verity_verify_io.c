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
struct bvec_iter {int dummy; } ;
struct dm_verity_io {unsigned int n_blocks; struct bvec_iter iter; scalar_t__ block; struct dm_verity* v; } ;
struct dm_verity {int /*<<< orphan*/  validated_blocks; int /*<<< orphan*/  digest_size; } ;
struct crypto_wait {int dummy; } ;
struct ahash_request {int dummy; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  DM_VERITY_BLOCK_TYPE_DATA ; 
 int EIO ; 
 scalar_t__ likely (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int test_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  verity_bv_skip_block (struct dm_verity*,struct dm_verity_io*,struct bvec_iter*) ; 
 int /*<<< orphan*/  verity_bv_zero ; 
 scalar_t__ verity_fec_decode (struct dm_verity*,struct dm_verity_io*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,struct bvec_iter*) ; 
 int verity_for_bv_block (struct dm_verity*,struct dm_verity_io*,struct bvec_iter*,int /*<<< orphan*/ ) ; 
 int verity_for_io_block (struct dm_verity*,struct dm_verity_io*,struct bvec_iter*,struct crypto_wait*) ; 
 scalar_t__ verity_handle_err (struct dm_verity*,int /*<<< orphan*/ ,scalar_t__) ; 
 int verity_hash_final (struct dm_verity*,struct ahash_request*,int /*<<< orphan*/ ,struct crypto_wait*) ; 
 int verity_hash_for_block (struct dm_verity*,struct dm_verity_io*,scalar_t__,int /*<<< orphan*/ ,int*) ; 
 int verity_hash_init (struct dm_verity*,struct ahash_request*,struct crypto_wait*) ; 
 struct ahash_request* verity_io_hash_req (struct dm_verity*,struct dm_verity_io*) ; 
 int /*<<< orphan*/  verity_io_real_digest (struct dm_verity*,struct dm_verity_io*) ; 
 int /*<<< orphan*/  verity_io_want_digest (struct dm_verity*,struct dm_verity_io*) ; 

__attribute__((used)) static int verity_verify_io(struct dm_verity_io *io)
{
	bool is_zero;
	struct dm_verity *v = io->v;
	struct bvec_iter start;
	unsigned b;
	struct crypto_wait wait;

	for (b = 0; b < io->n_blocks; b++) {
		int r;
		sector_t cur_block = io->block + b;
		struct ahash_request *req = verity_io_hash_req(v, io);

		if (v->validated_blocks &&
		    likely(test_bit(cur_block, v->validated_blocks))) {
			verity_bv_skip_block(v, io, &io->iter);
			continue;
		}

		r = verity_hash_for_block(v, io, cur_block,
					  verity_io_want_digest(v, io),
					  &is_zero);
		if (unlikely(r < 0))
			return r;

		if (is_zero) {
			/*
			 * If we expect a zero block, don't validate, just
			 * return zeros.
			 */
			r = verity_for_bv_block(v, io, &io->iter,
						verity_bv_zero);
			if (unlikely(r < 0))
				return r;

			continue;
		}

		r = verity_hash_init(v, req, &wait);
		if (unlikely(r < 0))
			return r;

		start = io->iter;
		r = verity_for_io_block(v, io, &io->iter, &wait);
		if (unlikely(r < 0))
			return r;

		r = verity_hash_final(v, req, verity_io_real_digest(v, io),
					&wait);
		if (unlikely(r < 0))
			return r;

		if (likely(memcmp(verity_io_real_digest(v, io),
				  verity_io_want_digest(v, io), v->digest_size) == 0)) {
			if (v->validated_blocks)
				set_bit(cur_block, v->validated_blocks);
			continue;
		}
		else if (verity_fec_decode(v, io, DM_VERITY_BLOCK_TYPE_DATA,
					   cur_block, NULL, &start) == 0)
			continue;
		else if (verity_handle_err(v, DM_VERITY_BLOCK_TYPE_DATA,
					   cur_block))
			return -EIO;
	}

	return 0;
}