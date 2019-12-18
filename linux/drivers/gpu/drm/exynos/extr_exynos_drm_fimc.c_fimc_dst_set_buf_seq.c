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
typedef  int u32 ;
struct fimc_context {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  EXYNOS_CIFCNTSEQ ; 
 int FIMC_BUF_START ; 
 int FIMC_BUF_STOP ; 
 int /*<<< orphan*/  fimc_mask_irq (struct fimc_context*,int) ; 
 int fimc_read (struct fimc_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_write (struct fimc_context*,int,int /*<<< orphan*/ ) ; 
 int hweight32 (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void fimc_dst_set_buf_seq(struct fimc_context *ctx, u32 buf_id,
		bool enqueue)
{
	unsigned long flags;
	u32 buf_num;
	u32 cfg;

	DRM_DEV_DEBUG_KMS(ctx->dev, "buf_id[%d]enqueu[%d]\n", buf_id, enqueue);

	spin_lock_irqsave(&ctx->lock, flags);

	cfg = fimc_read(ctx, EXYNOS_CIFCNTSEQ);

	if (enqueue)
		cfg |= (1 << buf_id);
	else
		cfg &= ~(1 << buf_id);

	fimc_write(ctx, cfg, EXYNOS_CIFCNTSEQ);

	buf_num = hweight32(cfg);

	if (enqueue && buf_num >= FIMC_BUF_START)
		fimc_mask_irq(ctx, true);
	else if (!enqueue && buf_num <= FIMC_BUF_STOP)
		fimc_mask_irq(ctx, false);

	spin_unlock_irqrestore(&ctx->lock, flags);
}