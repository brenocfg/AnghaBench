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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {scalar_t__ qlen; } ;
struct hifn_device {scalar_t__ started; TYPE_2__ queue; } ;
struct hifn_context {struct hifn_device* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  tfm; } ;
struct ablkcipher_request {TYPE_1__ base; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 scalar_t__ HIFN_QUEUE_LENGTH ; 
 struct hifn_context* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hifn_process_queue (struct hifn_device*) ; 
 int hifn_setup_crypto_req (struct ablkcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hifn_setup_crypto(struct ablkcipher_request *req, u8 op,
		u8 type, u8 mode)
{
	int err;
	struct hifn_context *ctx = crypto_tfm_ctx(req->base.tfm);
	struct hifn_device *dev = ctx->dev;

	err = hifn_setup_crypto_req(req, op, type, mode);
	if (err)
		return err;

	if (dev->started < HIFN_QUEUE_LENGTH &&	dev->queue.qlen)
		hifn_process_queue(dev);

	return -EINPROGRESS;
}