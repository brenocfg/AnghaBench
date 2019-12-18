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
typedef  int /*<<< orphan*/  u8 ;
struct dm_verity_io {int dummy; } ;
struct dm_verity {int hash_dev_block_bits; int /*<<< orphan*/  digest_size; int /*<<< orphan*/  bufio; } ;
struct dm_buffer {int dummy; } ;
struct buffer_aux {int hash_verified; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  DM_VERITY_BLOCK_TYPE_METADATA ; 
 int EIO ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 struct buffer_aux* dm_bufio_get_aux_data (struct dm_buffer*) ; 
 int /*<<< orphan*/ * dm_bufio_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dm_buffer**) ; 
 int /*<<< orphan*/  dm_bufio_release (struct dm_buffer*) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ verity_fec_decode (struct dm_verity*,struct dm_verity_io*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ verity_handle_err (struct dm_verity*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int verity_hash (struct dm_verity*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verity_hash_at_level (struct dm_verity*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  verity_io_hash_req (struct dm_verity*,struct dm_verity_io*) ; 
 int /*<<< orphan*/  verity_io_real_digest (struct dm_verity*,struct dm_verity_io*) ; 

__attribute__((used)) static int verity_verify_level(struct dm_verity *v, struct dm_verity_io *io,
			       sector_t block, int level, bool skip_unverified,
			       u8 *want_digest)
{
	struct dm_buffer *buf;
	struct buffer_aux *aux;
	u8 *data;
	int r;
	sector_t hash_block;
	unsigned offset;

	verity_hash_at_level(v, block, level, &hash_block, &offset);

	data = dm_bufio_read(v->bufio, hash_block, &buf);
	if (IS_ERR(data))
		return PTR_ERR(data);

	aux = dm_bufio_get_aux_data(buf);

	if (!aux->hash_verified) {
		if (skip_unverified) {
			r = 1;
			goto release_ret_r;
		}

		r = verity_hash(v, verity_io_hash_req(v, io),
				data, 1 << v->hash_dev_block_bits,
				verity_io_real_digest(v, io));
		if (unlikely(r < 0))
			goto release_ret_r;

		if (likely(memcmp(verity_io_real_digest(v, io), want_digest,
				  v->digest_size) == 0))
			aux->hash_verified = 1;
		else if (verity_fec_decode(v, io,
					   DM_VERITY_BLOCK_TYPE_METADATA,
					   hash_block, data, NULL) == 0)
			aux->hash_verified = 1;
		else if (verity_handle_err(v,
					   DM_VERITY_BLOCK_TYPE_METADATA,
					   hash_block)) {
			r = -EIO;
			goto release_ret_r;
		}
	}

	data += offset;
	memcpy(want_digest, data, v->digest_size);
	r = 0;

release_ret_r:
	dm_bufio_release(buf);
	return r;
}