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
struct dm_verity {int data_dev_block_bits; int /*<<< orphan*/  digest_size; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verity_hash (struct dm_verity*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verity_io_hash_req (struct dm_verity*,struct dm_verity_io*) ; 
 int /*<<< orphan*/  verity_io_real_digest (struct dm_verity*,struct dm_verity_io*) ; 

__attribute__((used)) static int fec_is_erasure(struct dm_verity *v, struct dm_verity_io *io,
			  u8 *want_digest, u8 *data)
{
	if (unlikely(verity_hash(v, verity_io_hash_req(v, io),
				 data, 1 << v->data_dev_block_bits,
				 verity_io_real_digest(v, io))))
		return 0;

	return memcmp(verity_io_real_digest(v, io), want_digest,
		      v->digest_size) != 0;
}