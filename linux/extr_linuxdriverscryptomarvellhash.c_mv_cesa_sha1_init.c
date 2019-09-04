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
struct mv_cesa_op_ctx {int dummy; } ;
struct mv_cesa_ahash_req {int /*<<< orphan*/ * state; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CESA_SA_DESC_CFG_MACM_SHA1 ; 
 int /*<<< orphan*/  SHA1_H0 ; 
 int /*<<< orphan*/  SHA1_H1 ; 
 int /*<<< orphan*/  SHA1_H2 ; 
 int /*<<< orphan*/  SHA1_H3 ; 
 int /*<<< orphan*/  SHA1_H4 ; 
 struct mv_cesa_ahash_req* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  mv_cesa_ahash_init (struct ahash_request*,struct mv_cesa_op_ctx*,int) ; 
 int /*<<< orphan*/  mv_cesa_set_op_cfg (struct mv_cesa_op_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv_cesa_sha1_init(struct ahash_request *req)
{
	struct mv_cesa_ahash_req *creq = ahash_request_ctx(req);
	struct mv_cesa_op_ctx tmpl = { };

	mv_cesa_set_op_cfg(&tmpl, CESA_SA_DESC_CFG_MACM_SHA1);

	mv_cesa_ahash_init(req, &tmpl, false);

	creq->state[0] = SHA1_H0;
	creq->state[1] = SHA1_H1;
	creq->state[2] = SHA1_H2;
	creq->state[3] = SHA1_H3;
	creq->state[4] = SHA1_H4;

	return 0;
}