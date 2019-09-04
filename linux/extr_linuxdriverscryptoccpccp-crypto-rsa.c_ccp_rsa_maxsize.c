#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct crypto_akcipher {int dummy; } ;
struct TYPE_3__ {unsigned int n_len; } ;
struct TYPE_4__ {TYPE_1__ rsa; } ;
struct ccp_ctx {TYPE_2__ u; } ;

/* Variables and functions */
 struct ccp_ctx* akcipher_tfm_ctx (struct crypto_akcipher*) ; 

__attribute__((used)) static unsigned int ccp_rsa_maxsize(struct crypto_akcipher *tfm)
{
	struct ccp_ctx *ctx = akcipher_tfm_ctx(tfm);

	return ctx->u.rsa.n_len;
}