#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cvm_req_ctx {int dummy; } ;
struct cvm_enc_ctx {int dummy; } ;
struct TYPE_2__ {int reqsize; } ;
struct crypto_tfm {TYPE_1__ crt_ablkcipher; } ;
struct ablkcipher_request {int dummy; } ;

/* Variables and functions */
 struct cvm_enc_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  memset (struct cvm_enc_ctx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cvm_enc_dec_init(struct crypto_tfm *tfm)
{
	struct cvm_enc_ctx *ctx = crypto_tfm_ctx(tfm);

	memset(ctx, 0, sizeof(*ctx));
	tfm->crt_ablkcipher.reqsize = sizeof(struct cvm_req_ctx) +
					sizeof(struct ablkcipher_request);
	/* Additional memory for ablkcipher_request is
	 * allocated since the cryptd daemon uses
	 * this memory for request_ctx information
	 */

	return 0;
}