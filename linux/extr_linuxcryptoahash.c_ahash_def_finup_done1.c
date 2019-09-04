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
struct TYPE_2__ {int /*<<< orphan*/  (* complete ) (TYPE_1__*,int) ;int /*<<< orphan*/  flags; } ;
struct ahash_request {TYPE_1__ base; scalar_t__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int EINPROGRESS ; 
 int ahash_def_finup_finish1 (struct ahash_request*,int) ; 
 int /*<<< orphan*/  ahash_notify_einprogress (struct ahash_request*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int) ; 

__attribute__((used)) static void ahash_def_finup_done1(struct crypto_async_request *req, int err)
{
	struct ahash_request *areq = req->data;

	if (err == -EINPROGRESS) {
		ahash_notify_einprogress(areq);
		return;
	}

	areq->base.flags &= ~CRYPTO_TFM_REQ_MAY_SLEEP;

	err = ahash_def_finup_finish1(areq, err);
	if (areq->priv)
		return;

	areq->base.complete(&areq->base, err);
}