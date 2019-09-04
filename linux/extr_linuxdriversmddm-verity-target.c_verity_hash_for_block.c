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
struct dm_verity {int levels; int /*<<< orphan*/  digest_size; scalar_t__ zero_digest; int /*<<< orphan*/  root_digest; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcmp (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int verity_verify_level (struct dm_verity*,struct dm_verity_io*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

int verity_hash_for_block(struct dm_verity *v, struct dm_verity_io *io,
			  sector_t block, u8 *digest, bool *is_zero)
{
	int r = 0, i;

	if (likely(v->levels)) {
		/*
		 * First, we try to get the requested hash for
		 * the current block. If the hash block itself is
		 * verified, zero is returned. If it isn't, this
		 * function returns 1 and we fall back to whole
		 * chain verification.
		 */
		r = verity_verify_level(v, io, block, 0, true, digest);
		if (likely(r <= 0))
			goto out;
	}

	memcpy(digest, v->root_digest, v->digest_size);

	for (i = v->levels - 1; i >= 0; i--) {
		r = verity_verify_level(v, io, block, i, false, digest);
		if (unlikely(r))
			goto out;
	}
out:
	if (!r && v->zero_digest)
		*is_zero = !memcmp(v->zero_digest, digest, v->digest_size);
	else
		*is_zero = false;

	return r;
}