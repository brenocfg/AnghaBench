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
struct crypto_tfm {int dummy; } ;
struct cc_cipher_ctx {int hw_key; } ;

/* Variables and functions */
 struct cc_cipher_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static inline bool cc_is_hw_key(struct crypto_tfm *tfm)
{
	struct cc_cipher_ctx *ctx_p = crypto_tfm_ctx(tfm);

	return ctx_p->hw_key;
}