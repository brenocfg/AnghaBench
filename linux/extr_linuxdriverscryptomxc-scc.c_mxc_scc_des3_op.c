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
struct mxc_scc_ctx {int dummy; } ;
struct ablkcipher_request {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int mxc_scc_ablkcipher_req_init (struct ablkcipher_request*,struct mxc_scc_ctx*) ; 
 int mxc_scc_queue_req (struct mxc_scc_ctx*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mxc_scc_des3_op(struct mxc_scc_ctx *ctx,
			   struct ablkcipher_request *req)
{
	int err;

	err = mxc_scc_ablkcipher_req_init(req, ctx);
	if (err)
		return err;

	return mxc_scc_queue_req(ctx, &req->base);
}