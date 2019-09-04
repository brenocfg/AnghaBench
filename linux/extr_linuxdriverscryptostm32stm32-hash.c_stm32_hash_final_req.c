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
struct stm32_hash_request_ctx {int bufcnt; int flags; int /*<<< orphan*/  buffer; } ;
struct stm32_hash_dev {struct ahash_request* req; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int HASH_FLAGS_CPU ; 
 struct stm32_hash_request_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int stm32_hash_dma_send (struct stm32_hash_dev*) ; 
 int stm32_hash_xmit_cpu (struct stm32_hash_dev*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int stm32_hash_final_req(struct stm32_hash_dev *hdev)
{
	struct ahash_request *req = hdev->req;
	struct stm32_hash_request_ctx *rctx = ahash_request_ctx(req);
	int err;
	int buflen = rctx->bufcnt;

	rctx->bufcnt = 0;

	if (!(rctx->flags & HASH_FLAGS_CPU))
		err = stm32_hash_dma_send(hdev);
	else
		err = stm32_hash_xmit_cpu(hdev, rctx->buffer, buflen, 1);


	return err;
}