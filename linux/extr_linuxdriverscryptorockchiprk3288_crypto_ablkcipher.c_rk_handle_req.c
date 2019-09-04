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
struct rk_crypto_info {int (* enqueue ) (struct rk_crypto_info*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  align_size; } ;
struct ablkcipher_request {int /*<<< orphan*/  base; int /*<<< orphan*/  nbytes; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IS_ALIGNED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct rk_crypto_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rk_handle_req(struct rk_crypto_info *dev,
			 struct ablkcipher_request *req)
{
	if (!IS_ALIGNED(req->nbytes, dev->align_size))
		return -EINVAL;
	else
		return dev->enqueue(dev, &req->base);
}