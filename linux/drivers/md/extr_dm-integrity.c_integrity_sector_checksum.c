#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct dm_integrity_c {int sectors_per_block; unsigned int tag_size; int /*<<< orphan*/  internal_hash; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  char __u8 ;
typedef  int /*<<< orphan*/  __u64 ;
struct TYPE_6__ {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int SECTOR_SHIFT ; 
 int /*<<< orphan*/  SHASH_DESC_ON_STACK (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 unsigned int crypto_shash_digestsize (int /*<<< orphan*/ ) ; 
 int crypto_shash_final (TYPE_1__*,char*) ; 
 int crypto_shash_init (TYPE_1__*) ; 
 int crypto_shash_update (TYPE_1__*,char const*,int) ; 
 int /*<<< orphan*/  dm_integrity_io_error (struct dm_integrity_c*,char*,int) ; 
 int /*<<< orphan*/  get_random_bytes (char*,unsigned int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_1__* req ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void integrity_sector_checksum(struct dm_integrity_c *ic, sector_t sector,
				      const char *data, char *result)
{
	__u64 sector_le = cpu_to_le64(sector);
	SHASH_DESC_ON_STACK(req, ic->internal_hash);
	int r;
	unsigned digest_size;

	req->tfm = ic->internal_hash;

	r = crypto_shash_init(req);
	if (unlikely(r < 0)) {
		dm_integrity_io_error(ic, "crypto_shash_init", r);
		goto failed;
	}

	r = crypto_shash_update(req, (const __u8 *)&sector_le, sizeof sector_le);
	if (unlikely(r < 0)) {
		dm_integrity_io_error(ic, "crypto_shash_update", r);
		goto failed;
	}

	r = crypto_shash_update(req, data, ic->sectors_per_block << SECTOR_SHIFT);
	if (unlikely(r < 0)) {
		dm_integrity_io_error(ic, "crypto_shash_update", r);
		goto failed;
	}

	r = crypto_shash_final(req, result);
	if (unlikely(r < 0)) {
		dm_integrity_io_error(ic, "crypto_shash_final", r);
		goto failed;
	}

	digest_size = crypto_shash_digestsize(ic->internal_hash);
	if (unlikely(digest_size < ic->tag_size))
		memset(result + digest_size, 0, ic->tag_size - digest_size);

	return;

failed:
	/* this shouldn't happen anyway, the hash functions have no reason to fail */
	get_random_bytes(result, ic->tag_size);
}