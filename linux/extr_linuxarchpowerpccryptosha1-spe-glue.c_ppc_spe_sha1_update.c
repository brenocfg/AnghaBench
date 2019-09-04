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
struct sha1_state {int count; scalar_t__ buffer; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 unsigned int MAX_BYTES ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/  const*,unsigned int const) ; 
 int /*<<< orphan*/  ppc_spe_sha1_transform (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 struct sha1_state* shash_desc_ctx (struct shash_desc*) ; 
 int /*<<< orphan*/  spe_begin () ; 
 int /*<<< orphan*/  spe_end () ; 

__attribute__((used)) static int ppc_spe_sha1_update(struct shash_desc *desc, const u8 *data,
			unsigned int len)
{
	struct sha1_state *sctx = shash_desc_ctx(desc);
	const unsigned int offset = sctx->count & 0x3f;
	const unsigned int avail = 64 - offset;
	unsigned int bytes;
	const u8 *src = data;

	if (avail > len) {
		sctx->count += len;
		memcpy((char *)sctx->buffer + offset, src, len);
		return 0;
	}

	sctx->count += len;

	if (offset) {
		memcpy((char *)sctx->buffer + offset, src, avail);

		spe_begin();
		ppc_spe_sha1_transform(sctx->state, (const u8 *)sctx->buffer, 1);
		spe_end();

		len -= avail;
		src += avail;
	}

	while (len > 63) {
		bytes = (len > MAX_BYTES) ? MAX_BYTES : len;
		bytes = bytes & ~0x3f;

		spe_begin();
		ppc_spe_sha1_transform(sctx->state, src, bytes >> 6);
		spe_end();

		src += bytes;
		len -= bytes;
	};

	memcpy((char *)sctx->buffer, src, len);
	return 0;
}