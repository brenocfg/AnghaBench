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
typedef  int /*<<< orphan*/  u32 ;
struct cpt_request_info {int /*<<< orphan*/  incnt; } ;
struct cvm_req_ctx {struct cpt_request_info cpt_req; } ;
struct ablkcipher_request {int /*<<< orphan*/  nbytes; int /*<<< orphan*/  src; int /*<<< orphan*/  info; } ;

/* Variables and functions */
 struct cvm_req_ctx* ablkcipher_request_ctx (struct ablkcipher_request*) ; 
 int /*<<< orphan*/  create_ctx_hdr (struct ablkcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_input_data (struct cpt_request_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_input_iv (struct cpt_request_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u32 create_input_list(struct ablkcipher_request  *req, u32 enc,
				    u32 enc_iv_len)
{
	struct cvm_req_ctx *rctx = ablkcipher_request_ctx(req);
	struct cpt_request_info *req_info = &rctx->cpt_req;
	u32 argcnt =  0;

	create_ctx_hdr(req, enc, &argcnt);
	update_input_iv(req_info, req->info, enc_iv_len, &argcnt);
	update_input_data(req_info, req->src, req->nbytes, &argcnt);
	req_info->incnt = argcnt;

	return 0;
}