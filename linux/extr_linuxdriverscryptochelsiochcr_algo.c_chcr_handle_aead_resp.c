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
struct chcr_aead_reqctx {scalar_t__ verify; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* complete ) (TYPE_1__*,int) ;} ;
struct aead_request {TYPE_1__ base; } ;

/* Variables and functions */
 scalar_t__ VERIFY_HW ; 
 scalar_t__ VERIFY_SW ; 
 struct chcr_aead_reqctx* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  chcr_aead_common_exit (struct aead_request*) ; 
 int /*<<< orphan*/  chcr_verify_tag (struct aead_request*,unsigned char*,int*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int) ; 

__attribute__((used)) static inline void chcr_handle_aead_resp(struct aead_request *req,
					 unsigned char *input,
					 int err)
{
	struct chcr_aead_reqctx *reqctx = aead_request_ctx(req);

	chcr_aead_common_exit(req);
	if (reqctx->verify == VERIFY_SW) {
		chcr_verify_tag(req, input, &err);
		reqctx->verify = VERIFY_HW;
	}
	req->base.complete(&req->base, err);
}