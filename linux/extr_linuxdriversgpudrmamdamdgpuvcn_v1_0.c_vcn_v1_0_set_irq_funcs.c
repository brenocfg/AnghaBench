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
struct TYPE_4__ {TYPE_1__ irq; scalar_t__ num_enc_rings; } ;
struct amdgpu_device {TYPE_2__ vcn; } ;

/* Variables and functions */
 int /*<<< orphan*/  vcn_v1_0_irq_funcs ; 

__attribute__((used)) static void vcn_v1_0_set_irq_funcs(struct amdgpu_device *adev)
{
	adev->vcn.irq.num_types = adev->vcn.num_enc_rings + 1;
	adev->vcn.irq.funcs = &vcn_v1_0_irq_funcs;
}