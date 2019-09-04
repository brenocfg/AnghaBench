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
struct crypto_tfm {int dummy; } ;
struct camellia_sparc64_ctx {int /*<<< orphan*/  key_len; int /*<<< orphan*/ * decrypt_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  camellia_sparc64_crypt (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct camellia_sparc64_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static void camellia_decrypt(struct crypto_tfm *tfm, u8 *dst, const u8 *src)
{
	struct camellia_sparc64_ctx *ctx = crypto_tfm_ctx(tfm);

	camellia_sparc64_crypt(&ctx->decrypt_key[0],
			       (const u32 *) src,
			       (u32 *) dst, ctx->key_len);
}