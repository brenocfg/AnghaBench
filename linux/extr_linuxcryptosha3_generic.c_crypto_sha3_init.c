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
struct shash_desc {int /*<<< orphan*/  tfm; } ;
struct sha3_state {int rsiz; int rsizw; int /*<<< orphan*/  st; scalar_t__ partial; } ;

/* Variables and functions */
 unsigned int crypto_shash_digestsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct sha3_state* shash_desc_ctx (struct shash_desc*) ; 

int crypto_sha3_init(struct shash_desc *desc)
{
	struct sha3_state *sctx = shash_desc_ctx(desc);
	unsigned int digest_size = crypto_shash_digestsize(desc->tfm);

	sctx->rsiz = 200 - 2 * digest_size;
	sctx->rsizw = sctx->rsiz / 8;
	sctx->partial = 0;

	memset(sctx->st, 0, sizeof(sctx->st));
	return 0;
}