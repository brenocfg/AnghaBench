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
typedef  int /*<<< orphan*/  u32 ;
struct des3_ede_ctx {int /*<<< orphan*/ * expkey; } ;
struct crypto_tfm {int /*<<< orphan*/  crt_flags; } ;

/* Variables and functions */
 int __des3_ede_setkey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 struct des3_ede_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static int des3_ede_setkey(struct crypto_tfm *tfm, const u8 *key,
			   unsigned int keylen)
{
	struct des3_ede_ctx *dctx = crypto_tfm_ctx(tfm);
	u32 *flags = &tfm->crt_flags;
	u32 *expkey = dctx->expkey;

	return __des3_ede_setkey(expkey, flags, key, keylen);
}