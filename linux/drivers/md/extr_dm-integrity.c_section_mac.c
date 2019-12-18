#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  sector; } ;
struct journal_entry {TYPE_1__ u; } ;
struct dm_integrity_c {unsigned int journal_section_entries; int /*<<< orphan*/  journal_mac; } ;
typedef  int /*<<< orphan*/  digest ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_8__ {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int EINVAL ; 
 int HASH_MAX_DIGESTSIZE ; 
 unsigned int JOURNAL_MAC_SIZE ; 
 int /*<<< orphan*/  SHASH_DESC_ON_STACK (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 struct journal_entry* access_journal_entry (struct dm_integrity_c*,unsigned int,unsigned int) ; 
 unsigned int crypto_shash_digestsize (int /*<<< orphan*/ ) ; 
 int crypto_shash_final (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int crypto_shash_init (TYPE_2__*) ; 
 int crypto_shash_update (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 TYPE_2__* desc ; 
 int /*<<< orphan*/  dm_integrity_io_error (struct dm_integrity_c*,char*,int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void section_mac(struct dm_integrity_c *ic, unsigned section, __u8 result[JOURNAL_MAC_SIZE])
{
	SHASH_DESC_ON_STACK(desc, ic->journal_mac);
	int r;
	unsigned j, size;

	desc->tfm = ic->journal_mac;

	r = crypto_shash_init(desc);
	if (unlikely(r)) {
		dm_integrity_io_error(ic, "crypto_shash_init", r);
		goto err;
	}

	for (j = 0; j < ic->journal_section_entries; j++) {
		struct journal_entry *je = access_journal_entry(ic, section, j);
		r = crypto_shash_update(desc, (__u8 *)&je->u.sector, sizeof je->u.sector);
		if (unlikely(r)) {
			dm_integrity_io_error(ic, "crypto_shash_update", r);
			goto err;
		}
	}

	size = crypto_shash_digestsize(ic->journal_mac);

	if (likely(size <= JOURNAL_MAC_SIZE)) {
		r = crypto_shash_final(desc, result);
		if (unlikely(r)) {
			dm_integrity_io_error(ic, "crypto_shash_final", r);
			goto err;
		}
		memset(result + size, 0, JOURNAL_MAC_SIZE - size);
	} else {
		__u8 digest[HASH_MAX_DIGESTSIZE];

		if (WARN_ON(size > sizeof(digest))) {
			dm_integrity_io_error(ic, "digest_size", -EINVAL);
			goto err;
		}
		r = crypto_shash_final(desc, digest);
		if (unlikely(r)) {
			dm_integrity_io_error(ic, "crypto_shash_final", r);
			goto err;
		}
		memcpy(result, digest, JOURNAL_MAC_SIZE);
	}

	return;
err:
	memset(result, 0, JOURNAL_MAC_SIZE);
}