#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* inst; } ;
struct amdgpu_device {TYPE_3__ uvd; } ;
struct TYPE_4__ {int num_types; int /*<<< orphan*/ * funcs; } ;
struct TYPE_5__ {TYPE_1__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  uvd_v5_0_irq_funcs ; 

__attribute__((used)) static void uvd_v5_0_set_irq_funcs(struct amdgpu_device *adev)
{
	adev->uvd.inst->irq.num_types = 1;
	adev->uvd.inst->irq.funcs = &uvd_v5_0_irq_funcs;
}