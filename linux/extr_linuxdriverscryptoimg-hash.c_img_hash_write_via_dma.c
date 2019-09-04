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
struct img_hash_request_ctx {int /*<<< orphan*/  total; } ;
struct img_hash_dev {int flags; int /*<<< orphan*/  dma_task; int /*<<< orphan*/  dev; int /*<<< orphan*/  req; } ;

/* Variables and functions */
 int DRIVER_FLAGS_DMA_ACTIVE ; 
 int DRIVER_FLAGS_FINAL ; 
 int EINPROGRESS ; 
 struct img_hash_request_ctx* ahash_request_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_hash_start (struct img_hash_dev*,int) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int img_hash_write_via_dma(struct img_hash_dev *hdev)
{
	struct img_hash_request_ctx *ctx = ahash_request_ctx(hdev->req);

	img_hash_start(hdev, true);

	dev_dbg(hdev->dev, "xmit dma size: %d\n", ctx->total);

	if (!ctx->total)
		hdev->flags |= DRIVER_FLAGS_FINAL;

	hdev->flags |= DRIVER_FLAGS_DMA_ACTIVE | DRIVER_FLAGS_FINAL;

	tasklet_schedule(&hdev->dma_task);

	return -EINPROGRESS;
}