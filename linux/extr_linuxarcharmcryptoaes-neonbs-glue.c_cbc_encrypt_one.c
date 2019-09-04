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
struct crypto_skcipher {int dummy; } ;
struct aesbs_cbc_ctx {int /*<<< orphan*/  enc_tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_cipher_encrypt_one (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 struct aesbs_cbc_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 

__attribute__((used)) static void cbc_encrypt_one(struct crypto_skcipher *tfm, const u8 *src, u8 *dst)
{
	struct aesbs_cbc_ctx *ctx = crypto_skcipher_ctx(tfm);

	crypto_cipher_encrypt_one(ctx->enc_tfm, dst, src);
}