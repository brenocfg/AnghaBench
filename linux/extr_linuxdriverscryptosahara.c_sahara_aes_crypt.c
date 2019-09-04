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
struct sahara_dev {int /*<<< orphan*/  kthread; int /*<<< orphan*/  queue_mutex; int /*<<< orphan*/  queue; int /*<<< orphan*/  device; } ;
struct sahara_aes_reqctx {unsigned long mode; } ;
struct ablkcipher_request {int /*<<< orphan*/  nbytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_BLOCK_SIZE ; 
 int EINVAL ; 
 unsigned long FLAGS_CBC ; 
 unsigned long FLAGS_ENCRYPT ; 
 int /*<<< orphan*/  IS_ALIGNED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ablkcipher_enqueue_request (int /*<<< orphan*/ *,struct ablkcipher_request*) ; 
 struct sahara_aes_reqctx* ablkcipher_request_ctx (struct ablkcipher_request*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct sahara_dev* dev_ptr ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sahara_aes_crypt(struct ablkcipher_request *req, unsigned long mode)
{
	struct sahara_aes_reqctx *rctx = ablkcipher_request_ctx(req);
	struct sahara_dev *dev = dev_ptr;
	int err = 0;

	dev_dbg(dev->device, "nbytes: %d, enc: %d, cbc: %d\n",
		req->nbytes, !!(mode & FLAGS_ENCRYPT), !!(mode & FLAGS_CBC));

	if (!IS_ALIGNED(req->nbytes, AES_BLOCK_SIZE)) {
		dev_err(dev->device,
			"request size is not exact amount of AES blocks\n");
		return -EINVAL;
	}

	rctx->mode = mode;

	mutex_lock(&dev->queue_mutex);
	err = ablkcipher_enqueue_request(&dev->queue, req);
	mutex_unlock(&dev->queue_mutex);

	wake_up_process(dev->kthread);

	return err;
}