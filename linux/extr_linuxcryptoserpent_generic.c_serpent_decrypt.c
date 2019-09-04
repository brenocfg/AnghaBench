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
struct serpent_ctx {int dummy; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __serpent_decrypt (struct serpent_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 struct serpent_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static void serpent_decrypt(struct crypto_tfm *tfm, u8 *dst, const u8 *src)
{
	struct serpent_ctx *ctx = crypto_tfm_ctx(tfm);

	__serpent_decrypt(ctx, dst, src);
}