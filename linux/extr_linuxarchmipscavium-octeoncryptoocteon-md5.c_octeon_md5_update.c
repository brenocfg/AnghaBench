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
typedef  char u8 ;
typedef  unsigned int u32 ;
struct shash_desc {int dummy; } ;
struct octeon_cop2_state {int dummy; } ;
struct md5_state {int byte_count; char const* block; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,unsigned int const) ; 
 int /*<<< orphan*/  octeon_crypto_disable (struct octeon_cop2_state*,unsigned long) ; 
 unsigned long octeon_crypto_enable (struct octeon_cop2_state*) ; 
 int /*<<< orphan*/  octeon_md5_read_hash (struct md5_state*) ; 
 int /*<<< orphan*/  octeon_md5_store_hash (struct md5_state*) ; 
 int /*<<< orphan*/  octeon_md5_transform (char const*) ; 
 struct md5_state* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int octeon_md5_update(struct shash_desc *desc, const u8 *data,
			     unsigned int len)
{
	struct md5_state *mctx = shash_desc_ctx(desc);
	const u32 avail = sizeof(mctx->block) - (mctx->byte_count & 0x3f);
	struct octeon_cop2_state state;
	unsigned long flags;

	mctx->byte_count += len;

	if (avail > len) {
		memcpy((char *)mctx->block + (sizeof(mctx->block) - avail),
		       data, len);
		return 0;
	}

	memcpy((char *)mctx->block + (sizeof(mctx->block) - avail), data,
	       avail);

	flags = octeon_crypto_enable(&state);
	octeon_md5_store_hash(mctx);

	octeon_md5_transform(mctx->block);
	data += avail;
	len -= avail;

	while (len >= sizeof(mctx->block)) {
		octeon_md5_transform(data);
		data += sizeof(mctx->block);
		len -= sizeof(mctx->block);
	}

	octeon_md5_read_hash(mctx);
	octeon_crypto_disable(&state, flags);

	memcpy(mctx->block, data, len);

	return 0;
}