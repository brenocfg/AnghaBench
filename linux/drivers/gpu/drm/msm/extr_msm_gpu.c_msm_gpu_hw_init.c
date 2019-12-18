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
struct msm_gpu {int needs_hw_init; int /*<<< orphan*/  irq; TYPE_2__* funcs; TYPE_1__* dev; } ;
struct TYPE_4__ {int (* hw_init ) (struct msm_gpu*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  struct_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int stub1 (struct msm_gpu*) ; 

int msm_gpu_hw_init(struct msm_gpu *gpu)
{
	int ret;

	WARN_ON(!mutex_is_locked(&gpu->dev->struct_mutex));

	if (!gpu->needs_hw_init)
		return 0;

	disable_irq(gpu->irq);
	ret = gpu->funcs->hw_init(gpu);
	if (!ret)
		gpu->needs_hw_init = false;
	enable_irq(gpu->irq);

	return ret;
}