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
struct rk_crypto_info {int aligned; int /*<<< orphan*/  lock; void* dst_nents; int /*<<< orphan*/  sg_dst; void* src_nents; int /*<<< orphan*/  first; int /*<<< orphan*/  sg_src; int /*<<< orphan*/  total; int /*<<< orphan*/  left_bytes; int /*<<< orphan*/  async_req; } ;
struct ablkcipher_request {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  nbytes; } ;

/* Variables and functions */
 struct ablkcipher_request* ablkcipher_request_cast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_ablk_hw_init (struct rk_crypto_info*) ; 
 int rk_set_data_start (struct rk_crypto_info*) ; 
 void* sg_nents (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int rk_ablk_start(struct rk_crypto_info *dev)
{
	struct ablkcipher_request *req =
		ablkcipher_request_cast(dev->async_req);
	unsigned long flags;
	int err = 0;

	dev->left_bytes = req->nbytes;
	dev->total = req->nbytes;
	dev->sg_src = req->src;
	dev->first = req->src;
	dev->src_nents = sg_nents(req->src);
	dev->sg_dst = req->dst;
	dev->dst_nents = sg_nents(req->dst);
	dev->aligned = 1;

	spin_lock_irqsave(&dev->lock, flags);
	rk_ablk_hw_init(dev);
	err = rk_set_data_start(dev);
	spin_unlock_irqrestore(&dev->lock, flags);
	return err;
}