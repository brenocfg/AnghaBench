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
struct stm32_crc_ctx {int /*<<< orphan*/  poly; int /*<<< orphan*/  key; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRC32C_POLY_LE ; 
 int /*<<< orphan*/  CRC_INIT_DEFAULT ; 
 struct stm32_crc_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static int stm32_crc32c_cra_init(struct crypto_tfm *tfm)
{
	struct stm32_crc_ctx *mctx = crypto_tfm_ctx(tfm);

	mctx->key = CRC_INIT_DEFAULT;
	mctx->poly = CRC32C_POLY_LE;
	return 0;
}