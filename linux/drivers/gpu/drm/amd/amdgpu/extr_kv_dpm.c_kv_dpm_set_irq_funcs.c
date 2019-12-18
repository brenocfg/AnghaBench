#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * funcs; int /*<<< orphan*/  num_types; } ;
struct TYPE_6__ {TYPE_1__ irq; } ;
struct TYPE_7__ {TYPE_2__ thermal; } ;
struct TYPE_8__ {TYPE_3__ dpm; } ;
struct amdgpu_device {TYPE_4__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_THERMAL_IRQ_LAST ; 
 int /*<<< orphan*/  kv_dpm_irq_funcs ; 

__attribute__((used)) static void kv_dpm_set_irq_funcs(struct amdgpu_device *adev)
{
	adev->pm.dpm.thermal.irq.num_types = AMDGPU_THERMAL_IRQ_LAST;
	adev->pm.dpm.thermal.irq.funcs = &kv_dpm_irq_funcs;
}