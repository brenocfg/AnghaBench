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
struct skcipher_request {int /*<<< orphan*/  base; int /*<<< orphan*/  cryptlen; } ;
struct mv_cesa_skcipher_req {int /*<<< orphan*/  base; } ;
struct mv_cesa_op_ctx {int dummy; } ;
struct mv_cesa_engine {int dummy; } ;

/* Variables and functions */
 int mv_cesa_queue_req (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mv_cesa_req_needs_cleanup (int /*<<< orphan*/ *,int) ; 
 struct mv_cesa_engine* mv_cesa_select_engine (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_cesa_skcipher_cleanup (struct skcipher_request*) ; 
 int /*<<< orphan*/  mv_cesa_skcipher_prepare (int /*<<< orphan*/ *,struct mv_cesa_engine*) ; 
 int mv_cesa_skcipher_req_init (struct skcipher_request*,struct mv_cesa_op_ctx*) ; 
 struct mv_cesa_skcipher_req* skcipher_request_ctx (struct skcipher_request*) ; 

__attribute__((used)) static int mv_cesa_skcipher_queue_req(struct skcipher_request *req,
				      struct mv_cesa_op_ctx *tmpl)
{
	int ret;
	struct mv_cesa_skcipher_req *creq = skcipher_request_ctx(req);
	struct mv_cesa_engine *engine;

	ret = mv_cesa_skcipher_req_init(req, tmpl);
	if (ret)
		return ret;

	engine = mv_cesa_select_engine(req->cryptlen);
	mv_cesa_skcipher_prepare(&req->base, engine);

	ret = mv_cesa_queue_req(&req->base, &creq->base);

	if (mv_cesa_req_needs_cleanup(&req->base, ret))
		mv_cesa_skcipher_cleanup(req);

	return ret;
}