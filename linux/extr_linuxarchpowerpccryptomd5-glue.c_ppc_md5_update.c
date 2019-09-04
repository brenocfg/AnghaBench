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
struct shash_desc {int dummy; } ;
struct md5_state {int byte_count; scalar_t__ block; int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  ppc_md5_transform (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 struct md5_state* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int ppc_md5_update(struct shash_desc *desc, const u8 *data,
			unsigned int len)
{
	struct md5_state *sctx = shash_desc_ctx(desc);
	const unsigned int offset = sctx->byte_count & 0x3f;
	unsigned int avail = 64 - offset;
	const u8 *src = data;

	sctx->byte_count += len;

	if (avail > len) {
		memcpy((char *)sctx->block + offset, src, len);
		return 0;
	}

	if (offset) {
		memcpy((char *)sctx->block + offset, src, avail);
		ppc_md5_transform(sctx->hash, (const u8 *)sctx->block, 1);
		len -= avail;
		src += avail;
	}

	if (len > 63) {
		ppc_md5_transform(sctx->hash, src, len >> 6);
		src += len & ~0x3f;
		len &= 0x3f;
	}

	memcpy((char *)sctx->block, src, len);
	return 0;
}