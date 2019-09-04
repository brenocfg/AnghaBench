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
struct atmel_sha_reqctx {int op; } ;
struct atmel_sha_dev {int /*<<< orphan*/  resume; struct ahash_request* req; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SHA_OP_DIGEST 131 
#define  SHA_OP_FINAL 130 
#define  SHA_OP_INIT 129 
#define  SHA_OP_UPDATE 128 
 struct atmel_sha_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 int atmel_sha_complete (struct atmel_sha_dev*,int) ; 
 int /*<<< orphan*/  atmel_sha_done ; 
 int atmel_sha_final_req (struct atmel_sha_dev*) ; 
 int /*<<< orphan*/  atmel_sha_hmac_digest2 ; 
 int /*<<< orphan*/  atmel_sha_hmac_final ; 
 int /*<<< orphan*/  atmel_sha_hmac_init_done ; 
 int atmel_sha_hmac_setup (struct atmel_sha_dev*,int /*<<< orphan*/ ) ; 
 int atmel_sha_hw_init (struct atmel_sha_dev*) ; 
 int atmel_sha_update_req (struct atmel_sha_dev*) ; 

__attribute__((used)) static int atmel_sha_hmac_start(struct atmel_sha_dev *dd)
{
	struct ahash_request *req = dd->req;
	struct atmel_sha_reqctx *ctx = ahash_request_ctx(req);
	int err;

	err = atmel_sha_hw_init(dd);
	if (err)
		return atmel_sha_complete(dd, err);

	switch (ctx->op) {
	case SHA_OP_INIT:
		err = atmel_sha_hmac_setup(dd, atmel_sha_hmac_init_done);
		break;

	case SHA_OP_UPDATE:
		dd->resume = atmel_sha_done;
		err = atmel_sha_update_req(dd);
		break;

	case SHA_OP_FINAL:
		dd->resume = atmel_sha_hmac_final;
		err = atmel_sha_final_req(dd);
		break;

	case SHA_OP_DIGEST:
		err = atmel_sha_hmac_setup(dd, atmel_sha_hmac_digest2);
		break;

	default:
		return atmel_sha_complete(dd, -EINVAL);
	}

	return err;
}