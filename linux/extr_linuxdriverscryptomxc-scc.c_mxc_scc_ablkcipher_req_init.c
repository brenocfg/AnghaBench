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
struct mxc_scc_ctx {int src_nents; int dst_nents; scalar_t__ offset; scalar_t__ size; struct mxc_scc* scc; } ;
struct mxc_scc {int /*<<< orphan*/  dev; } ;
struct ablkcipher_request {int /*<<< orphan*/  nbytes; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int sg_nents_for_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mxc_scc_ablkcipher_req_init(struct ablkcipher_request *req,
				       struct mxc_scc_ctx *ctx)
{
	struct mxc_scc *scc = ctx->scc;
	int nents;

	nents = sg_nents_for_len(req->src, req->nbytes);
	if (nents < 0) {
		dev_err(scc->dev, "Invalid number of src SC");
		return nents;
	}
	ctx->src_nents = nents;

	nents = sg_nents_for_len(req->dst, req->nbytes);
	if (nents < 0) {
		dev_err(scc->dev, "Invalid number of dst SC");
		return nents;
	}
	ctx->dst_nents = nents;

	ctx->size = 0;
	ctx->offset = 0;

	return 0;
}