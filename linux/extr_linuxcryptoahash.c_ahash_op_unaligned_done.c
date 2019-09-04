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
struct crypto_async_request {struct ahash_request* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* complete ) (TYPE_1__*,int) ;} ;
struct ahash_request {TYPE_1__ base; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int /*<<< orphan*/  ahash_notify_einprogress (struct ahash_request*) ; 
 int /*<<< orphan*/  ahash_restore_req (struct ahash_request*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int) ; 

__attribute__((used)) static void ahash_op_unaligned_done(struct crypto_async_request *req, int err)
{
	struct ahash_request *areq = req->data;

	if (err == -EINPROGRESS) {
		ahash_notify_einprogress(areq);
		return;
	}

	/*
	 * Restore the original request, see ahash_op_unaligned() for what
	 * goes where.
	 *
	 * The "struct ahash_request *req" here is in fact the "req.base"
	 * from the ADJUSTED request from ahash_op_unaligned(), thus as it
	 * is a pointer to self, it is also the ADJUSTED "req" .
	 */

	/* First copy req->result into req->priv.result */
	ahash_restore_req(areq, err);

	/* Complete the ORIGINAL request. */
	areq->base.complete(&areq->base, err);
}