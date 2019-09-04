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
struct poly1305_desc_ctx {int sset; int rset; } ;

/* Variables and functions */
 unsigned int POLY1305_BLOCK_SIZE ; 
 int /*<<< orphan*/  poly1305_setrkey (struct poly1305_desc_ctx*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  poly1305_setskey (struct poly1305_desc_ctx*,int /*<<< orphan*/  const*) ; 

unsigned int crypto_poly1305_setdesckey(struct poly1305_desc_ctx *dctx,
					const u8 *src, unsigned int srclen)
{
	if (!dctx->sset) {
		if (!dctx->rset && srclen >= POLY1305_BLOCK_SIZE) {
			poly1305_setrkey(dctx, src);
			src += POLY1305_BLOCK_SIZE;
			srclen -= POLY1305_BLOCK_SIZE;
			dctx->rset = true;
		}
		if (srclen >= POLY1305_BLOCK_SIZE) {
			poly1305_setskey(dctx, src);
			src += POLY1305_BLOCK_SIZE;
			srclen -= POLY1305_BLOCK_SIZE;
			dctx->sset = true;
		}
	}
	return srclen;
}