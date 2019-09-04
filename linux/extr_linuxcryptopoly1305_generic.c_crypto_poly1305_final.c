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
typedef  int u64 ;
typedef  int u32 ;
struct shash_desc {int dummy; } ;
struct poly1305_desc_ctx {int buflen; int* buf; int* h; int* s; int /*<<< orphan*/  sset; } ;

/* Variables and functions */
 int ENOKEY ; 
 scalar_t__ POLY1305_BLOCK_SIZE ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  poly1305_blocks (struct poly1305_desc_ctx*,int*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int,int /*<<< orphan*/ *) ; 
 struct poly1305_desc_ctx* shash_desc_ctx (struct shash_desc*) ; 
 scalar_t__ unlikely (int) ; 

int crypto_poly1305_final(struct shash_desc *desc, u8 *dst)
{
	struct poly1305_desc_ctx *dctx = shash_desc_ctx(desc);
	u32 h0, h1, h2, h3, h4;
	u32 g0, g1, g2, g3, g4;
	u32 mask;
	u64 f = 0;

	if (unlikely(!dctx->sset))
		return -ENOKEY;

	if (unlikely(dctx->buflen)) {
		dctx->buf[dctx->buflen++] = 1;
		memset(dctx->buf + dctx->buflen, 0,
		       POLY1305_BLOCK_SIZE - dctx->buflen);
		poly1305_blocks(dctx, dctx->buf, POLY1305_BLOCK_SIZE, 0);
	}

	/* fully carry h */
	h0 = dctx->h[0];
	h1 = dctx->h[1];
	h2 = dctx->h[2];
	h3 = dctx->h[3];
	h4 = dctx->h[4];

	h2 += (h1 >> 26);     h1 = h1 & 0x3ffffff;
	h3 += (h2 >> 26);     h2 = h2 & 0x3ffffff;
	h4 += (h3 >> 26);     h3 = h3 & 0x3ffffff;
	h0 += (h4 >> 26) * 5; h4 = h4 & 0x3ffffff;
	h1 += (h0 >> 26);     h0 = h0 & 0x3ffffff;

	/* compute h + -p */
	g0 = h0 + 5;
	g1 = h1 + (g0 >> 26);             g0 &= 0x3ffffff;
	g2 = h2 + (g1 >> 26);             g1 &= 0x3ffffff;
	g3 = h3 + (g2 >> 26);             g2 &= 0x3ffffff;
	g4 = h4 + (g3 >> 26) - (1 << 26); g3 &= 0x3ffffff;

	/* select h if h < p, or h + -p if h >= p */
	mask = (g4 >> ((sizeof(u32) * 8) - 1)) - 1;
	g0 &= mask;
	g1 &= mask;
	g2 &= mask;
	g3 &= mask;
	g4 &= mask;
	mask = ~mask;
	h0 = (h0 & mask) | g0;
	h1 = (h1 & mask) | g1;
	h2 = (h2 & mask) | g2;
	h3 = (h3 & mask) | g3;
	h4 = (h4 & mask) | g4;

	/* h = h % (2^128) */
	h0 = (h0 >>  0) | (h1 << 26);
	h1 = (h1 >>  6) | (h2 << 20);
	h2 = (h2 >> 12) | (h3 << 14);
	h3 = (h3 >> 18) | (h4 <<  8);

	/* mac = (h + s) % (2^128) */
	f = (f >> 32) + h0 + dctx->s[0]; put_unaligned_le32(f, dst +  0);
	f = (f >> 32) + h1 + dctx->s[1]; put_unaligned_le32(f, dst +  4);
	f = (f >> 32) + h2 + dctx->s[2]; put_unaligned_le32(f, dst +  8);
	f = (f >> 32) + h3 + dctx->s[3]; put_unaligned_le32(f, dst + 12);

	return 0;
}