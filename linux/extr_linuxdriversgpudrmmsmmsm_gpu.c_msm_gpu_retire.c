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
struct msm_gpu {int /*<<< orphan*/  retire_work; TYPE_1__* dev; } ;
struct msm_drm_private {int /*<<< orphan*/  wq; } ;
struct TYPE_2__ {struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_sw_cntrs (struct msm_gpu*) ; 

void msm_gpu_retire(struct msm_gpu *gpu)
{
	struct msm_drm_private *priv = gpu->dev->dev_private;
	queue_work(priv->wq, &gpu->retire_work);
	update_sw_cntrs(gpu);
}