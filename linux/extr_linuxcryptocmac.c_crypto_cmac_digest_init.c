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
struct shash_desc {int /*<<< orphan*/  tfm; } ;
struct cmac_desc_ctx {scalar_t__ len; scalar_t__ ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/ * PTR_ALIGN (void*,unsigned long) ; 
 unsigned long crypto_shash_alignmask (int /*<<< orphan*/ ) ; 
 int crypto_shash_blocksize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct cmac_desc_ctx* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int crypto_cmac_digest_init(struct shash_desc *pdesc)
{
	unsigned long alignmask = crypto_shash_alignmask(pdesc->tfm);
	struct cmac_desc_ctx *ctx = shash_desc_ctx(pdesc);
	int bs = crypto_shash_blocksize(pdesc->tfm);
	u8 *prev = PTR_ALIGN((void *)ctx->ctx, alignmask + 1) + bs;

	ctx->len = 0;
	memset(prev, 0, bs);

	return 0;
}