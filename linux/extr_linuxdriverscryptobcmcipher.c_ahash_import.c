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
struct spu_hash_export_s {int /*<<< orphan*/  incr_hash; int /*<<< orphan*/  hash_carry_len; int /*<<< orphan*/  hash_carry; int /*<<< orphan*/  is_sw_hmac; int /*<<< orphan*/  total_sent; int /*<<< orphan*/  total_todo; } ;
struct iproc_reqctx_s {int /*<<< orphan*/  incr_hash; int /*<<< orphan*/  hash_carry_len; int /*<<< orphan*/  hash_carry; int /*<<< orphan*/  is_sw_hmac; int /*<<< orphan*/  total_sent; int /*<<< orphan*/  total_todo; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 struct iproc_reqctx_s* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ahash_import(struct ahash_request *req, const void *in)
{
	struct iproc_reqctx_s *rctx = ahash_request_ctx(req);
	struct spu_hash_export_s *spu_exp = (struct spu_hash_export_s *)in;

	rctx->total_todo = spu_exp->total_todo;
	rctx->total_sent = spu_exp->total_sent;
	rctx->is_sw_hmac = spu_exp->is_sw_hmac;
	memcpy(rctx->hash_carry, spu_exp->hash_carry, sizeof(rctx->hash_carry));
	rctx->hash_carry_len = spu_exp->hash_carry_len;
	memcpy(rctx->incr_hash, spu_exp->incr_hash, sizeof(rctx->incr_hash));

	return 0;
}