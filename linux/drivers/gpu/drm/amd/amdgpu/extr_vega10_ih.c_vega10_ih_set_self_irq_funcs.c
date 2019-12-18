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
struct TYPE_3__ {int /*<<< orphan*/ * funcs; scalar_t__ num_types; } ;
struct TYPE_4__ {TYPE_1__ self_irq; } ;
struct amdgpu_device {TYPE_2__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  vega10_ih_self_irq_funcs ; 

__attribute__((used)) static void vega10_ih_set_self_irq_funcs(struct amdgpu_device *adev)
{
	adev->irq.self_irq.num_types = 0;
	adev->irq.self_irq.funcs = &vega10_ih_self_irq_funcs;
}