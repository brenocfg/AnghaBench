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
struct TYPE_2__ {int flags; } ;
struct kpp_request {scalar_t__ src_len; int /*<<< orphan*/  src; TYPE_1__ base; } ;
struct crypto_kpp {int dummy; } ;
struct atmel_ecdh_ctx {int /*<<< orphan*/  fallback; scalar_t__ do_fallback; } ;
struct atmel_ecc_work_data {int /*<<< orphan*/  cmd; struct atmel_ecdh_ctx* ctx; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ ATMEL_ECC_PUBKEY_SIZE ; 
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atmel_ecc_enqueue (struct atmel_ecc_work_data*,int /*<<< orphan*/ ,struct kpp_request*) ; 
 int atmel_ecc_init_ecdh_cmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_ecdh_done ; 
 int crypto_kpp_compute_shared_secret (struct kpp_request*) ; 
 struct crypto_kpp* crypto_kpp_reqtfm (struct kpp_request*) ; 
 int /*<<< orphan*/  kfree (struct atmel_ecc_work_data*) ; 
 struct atmel_ecc_work_data* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kpp_request_set_tfm (struct kpp_request*,int /*<<< orphan*/ ) ; 
 struct atmel_ecdh_ctx* kpp_tfm_ctx (struct crypto_kpp*) ; 

__attribute__((used)) static int atmel_ecdh_compute_shared_secret(struct kpp_request *req)
{
	struct crypto_kpp *tfm = crypto_kpp_reqtfm(req);
	struct atmel_ecdh_ctx *ctx = kpp_tfm_ctx(tfm);
	struct atmel_ecc_work_data *work_data;
	gfp_t gfp;
	int ret;

	if (ctx->do_fallback) {
		kpp_request_set_tfm(req, ctx->fallback);
		return crypto_kpp_compute_shared_secret(req);
	}

	/* must have exactly two points to be on the curve */
	if (req->src_len != ATMEL_ECC_PUBKEY_SIZE)
		return -EINVAL;

	gfp = (req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP) ? GFP_KERNEL :
							     GFP_ATOMIC;

	work_data = kmalloc(sizeof(*work_data), gfp);
	if (!work_data)
		return -ENOMEM;

	work_data->ctx = ctx;

	ret = atmel_ecc_init_ecdh_cmd(&work_data->cmd, req->src);
	if (ret)
		goto free_work_data;

	atmel_ecc_enqueue(work_data, atmel_ecdh_done, req);

	return -EINPROGRESS;

free_work_data:
	kfree(work_data);
	return ret;
}