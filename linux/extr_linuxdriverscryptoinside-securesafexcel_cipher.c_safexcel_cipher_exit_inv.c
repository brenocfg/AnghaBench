#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct safexcel_inv_result {int error; int /*<<< orphan*/  completion; } ;
struct safexcel_crypto_priv {int /*<<< orphan*/  dev; TYPE_3__* ring; } ;
struct safexcel_cipher_req {int needs_inv; } ;
struct TYPE_4__ {int ring; int exit_inv; } ;
struct safexcel_cipher_ctx {TYPE_1__ base; struct safexcel_crypto_priv* priv; } ;
struct crypto_tfm {int dummy; } ;
struct crypto_async_request {struct crypto_tfm* tfm; } ;
struct TYPE_5__ {int /*<<< orphan*/  work; } ;
struct TYPE_6__ {TYPE_2__ work_data; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_enqueue_request (int /*<<< orphan*/ *,struct crypto_async_request*) ; 
 struct safexcel_cipher_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int safexcel_cipher_exit_inv(struct crypto_tfm *tfm,
				    struct crypto_async_request *base,
				    struct safexcel_cipher_req *sreq,
				    struct safexcel_inv_result *result)
{
	struct safexcel_cipher_ctx *ctx = crypto_tfm_ctx(tfm);
	struct safexcel_crypto_priv *priv = ctx->priv;
	int ring = ctx->base.ring;

	init_completion(&result->completion);

	ctx = crypto_tfm_ctx(base->tfm);
	ctx->base.exit_inv = true;
	sreq->needs_inv = true;

	spin_lock_bh(&priv->ring[ring].queue_lock);
	crypto_enqueue_request(&priv->ring[ring].queue, base);
	spin_unlock_bh(&priv->ring[ring].queue_lock);

	queue_work(priv->ring[ring].workqueue,
		   &priv->ring[ring].work_data.work);

	wait_for_completion(&result->completion);

	if (result->error) {
		dev_warn(priv->dev,
			"cipher: sync: invalidate: completion error %d\n",
			 result->error);
		return result->error;
	}

	return 0;
}