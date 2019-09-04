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
struct chachapoly_req_ctx {scalar_t__ cryptlen; int /*<<< orphan*/  tag; } ;
struct aead_request {scalar_t__ assoclen; int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 struct chachapoly_req_ctx* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int) ; 

__attribute__((used)) static int poly_copy_tag(struct aead_request *req)
{
	struct chachapoly_req_ctx *rctx = aead_request_ctx(req);

	scatterwalk_map_and_copy(rctx->tag, req->dst,
				 req->assoclen + rctx->cryptlen,
				 sizeof(rctx->tag), 1);
	return 0;
}