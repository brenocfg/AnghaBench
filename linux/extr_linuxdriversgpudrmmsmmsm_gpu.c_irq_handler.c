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
struct msm_gpu {TYPE_1__* funcs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* irq ) (struct msm_gpu*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct msm_gpu*) ; 

__attribute__((used)) static irqreturn_t irq_handler(int irq, void *data)
{
	struct msm_gpu *gpu = data;
	return gpu->funcs->irq(gpu);
}