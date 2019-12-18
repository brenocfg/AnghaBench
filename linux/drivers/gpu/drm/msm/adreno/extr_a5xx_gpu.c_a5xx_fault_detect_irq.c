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
struct msm_ringbuffer {int id; int /*<<< orphan*/  seqno; } ;
struct msm_gpu {int /*<<< orphan*/  recover_work; int /*<<< orphan*/  hangcheck_timer; TYPE_1__* funcs; struct drm_device* dev; } ;
struct msm_drm_private {int /*<<< orphan*/  wq; } ;
struct drm_device {int /*<<< orphan*/  dev; struct msm_drm_private* dev_private; } ;
struct TYPE_2__ {struct msm_ringbuffer* (* active_ring ) (struct msm_gpu*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_A5XX_CP_IB1_BASE ; 
 int /*<<< orphan*/  REG_A5XX_CP_IB1_BASE_HI ; 
 int /*<<< orphan*/  REG_A5XX_CP_IB1_BUFSZ ; 
 int /*<<< orphan*/  REG_A5XX_CP_IB2_BASE ; 
 int /*<<< orphan*/  REG_A5XX_CP_IB2_BASE_HI ; 
 int /*<<< orphan*/  REG_A5XX_CP_IB2_BUFSZ ; 
 int /*<<< orphan*/  REG_A5XX_CP_RB_RPTR ; 
 int /*<<< orphan*/  REG_A5XX_CP_RB_WPTR ; 
 int /*<<< orphan*/  REG_A5XX_RBBM_STATUS ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpu_read (struct msm_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_read64 (struct msm_gpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct msm_ringbuffer* stub1 (struct msm_gpu*) ; 

__attribute__((used)) static void a5xx_fault_detect_irq(struct msm_gpu *gpu)
{
	struct drm_device *dev = gpu->dev;
	struct msm_drm_private *priv = dev->dev_private;
	struct msm_ringbuffer *ring = gpu->funcs->active_ring(gpu);

	DRM_DEV_ERROR(dev->dev, "gpu fault ring %d fence %x status %8.8X rb %4.4x/%4.4x ib1 %16.16llX/%4.4x ib2 %16.16llX/%4.4x\n",
		ring ? ring->id : -1, ring ? ring->seqno : 0,
		gpu_read(gpu, REG_A5XX_RBBM_STATUS),
		gpu_read(gpu, REG_A5XX_CP_RB_RPTR),
		gpu_read(gpu, REG_A5XX_CP_RB_WPTR),
		gpu_read64(gpu, REG_A5XX_CP_IB1_BASE, REG_A5XX_CP_IB1_BASE_HI),
		gpu_read(gpu, REG_A5XX_CP_IB1_BUFSZ),
		gpu_read64(gpu, REG_A5XX_CP_IB2_BASE, REG_A5XX_CP_IB2_BASE_HI),
		gpu_read(gpu, REG_A5XX_CP_IB2_BUFSZ));

	/* Turn off the hangcheck timer to keep it from bothering us */
	del_timer(&gpu->hangcheck_timer);

	queue_work(priv->wq, &gpu->recover_work);
}