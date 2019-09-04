#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct skcipher_request {int /*<<< orphan*/  iv; } ;
struct TYPE_3__ {int /*<<< orphan*/  iv; } ;
struct TYPE_4__ {TYPE_1__ blkcipher; } ;
struct mv_cesa_op_ctx {TYPE_2__ ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DES3_EDE_BLOCK_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mv_cesa_des3_op (struct skcipher_request*,struct mv_cesa_op_ctx*) ; 

__attribute__((used)) static int mv_cesa_cbc_des3_op(struct skcipher_request *req,
			       struct mv_cesa_op_ctx *tmpl)
{
	memcpy(tmpl->ctx.blkcipher.iv, req->iv, DES3_EDE_BLOCK_SIZE);

	return mv_cesa_des3_op(req, tmpl);
}