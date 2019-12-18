#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct dm_verity_io {int dummy; } ;
struct dm_verity_fec_io {scalar_t__ level; scalar_t__ output_pos; int /*<<< orphan*/  output; } ;
struct dm_verity {int data_dev_block_bits; TYPE_2__* fec; scalar_t__ data_blocks; TYPE_1__* data_dev; } ;
struct bvec_iter {int dummy; } ;
typedef  int sector_t ;
typedef  enum verity_block_type { ____Placeholder_verity_block_type } verity_block_type ;
struct TYPE_4__ {int rounds; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN_LIMIT (char*,int /*<<< orphan*/ ) ; 
 int DM_VERITY_BLOCK_TYPE_METADATA ; 
 scalar_t__ DM_VERITY_FEC_MAX_RECURSION ; 
 int EIO ; 
 int EOPNOTSUPP ; 
 int div64_u64 (int,int) ; 
 int /*<<< orphan*/  fec_bv_copy ; 
 int fec_decode_rsb (struct dm_verity*,struct dm_verity_io*,struct dm_verity_fec_io*,int,int,int) ; 
 struct dm_verity_fec_io* fec_io (struct dm_verity_io*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  verity_fec_is_enabled (struct dm_verity*) ; 
 int verity_for_bv_block (struct dm_verity*,struct dm_verity_io*,struct bvec_iter*,int /*<<< orphan*/ ) ; 

int verity_fec_decode(struct dm_verity *v, struct dm_verity_io *io,
		      enum verity_block_type type, sector_t block, u8 *dest,
		      struct bvec_iter *iter)
{
	int r;
	struct dm_verity_fec_io *fio = fec_io(io);
	u64 offset, res, rsb;

	if (!verity_fec_is_enabled(v))
		return -EOPNOTSUPP;

	if (fio->level >= DM_VERITY_FEC_MAX_RECURSION) {
		DMWARN_LIMIT("%s: FEC: recursion too deep", v->data_dev->name);
		return -EIO;
	}

	fio->level++;

	if (type == DM_VERITY_BLOCK_TYPE_METADATA)
		block += v->data_blocks;

	/*
	 * For RS(M, N), the continuous FEC data is divided into blocks of N
	 * bytes. Since block size may not be divisible by N, the last block
	 * is zero padded when decoding.
	 *
	 * Each byte of the block is covered by a different RS(M, N) code,
	 * and each code is interleaved over N blocks to make it less likely
	 * that bursty corruption will leave us in unrecoverable state.
	 */

	offset = block << v->data_dev_block_bits;
	res = div64_u64(offset, v->fec->rounds << v->data_dev_block_bits);

	/*
	 * The base RS block we can feed to the interleaver to find out all
	 * blocks required for decoding.
	 */
	rsb = offset - res * (v->fec->rounds << v->data_dev_block_bits);

	/*
	 * Locating erasures is slow, so attempt to recover the block without
	 * them first. Do a second attempt with erasures if the corruption is
	 * bad enough.
	 */
	r = fec_decode_rsb(v, io, fio, rsb, offset, false);
	if (r < 0) {
		r = fec_decode_rsb(v, io, fio, rsb, offset, true);
		if (r < 0)
			goto done;
	}

	if (dest)
		memcpy(dest, fio->output, 1 << v->data_dev_block_bits);
	else if (iter) {
		fio->output_pos = 0;
		r = verity_for_bv_block(v, io, iter, fec_bv_copy);
	}

done:
	fio->level--;
	return r;
}