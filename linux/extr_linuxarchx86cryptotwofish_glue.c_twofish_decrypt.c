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
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  twofish_dec_blk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void twofish_decrypt(struct crypto_tfm *tfm, u8 *dst, const u8 *src)
{
	twofish_dec_blk(crypto_tfm_ctx(tfm), dst, src);
}