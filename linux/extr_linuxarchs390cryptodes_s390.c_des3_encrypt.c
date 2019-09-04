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
struct s390_des_ctx {int /*<<< orphan*/  key; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPACF_KM_TDEA_192 ; 
 int /*<<< orphan*/  DES_BLOCK_SIZE ; 
 int /*<<< orphan*/  cpacf_km (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 struct s390_des_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static void des3_encrypt(struct crypto_tfm *tfm, u8 *dst, const u8 *src)
{
	struct s390_des_ctx *ctx = crypto_tfm_ctx(tfm);

	cpacf_km(CPACF_KM_TDEA_192, ctx->key, dst, src, DES_BLOCK_SIZE);
}