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
struct TYPE_5__ {int num_types; int /*<<< orphan*/ * funcs; } ;
struct TYPE_7__ {int num_types; int /*<<< orphan*/ * funcs; } ;
struct TYPE_6__ {int /*<<< orphan*/ * funcs; int /*<<< orphan*/  num_types; } ;
struct TYPE_8__ {TYPE_1__ priv_inst_irq; TYPE_3__ priv_reg_irq; TYPE_2__ eop_irq; } ;
struct amdgpu_device {TYPE_4__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_CP_IRQ_LAST ; 
 int /*<<< orphan*/  gfx_v7_0_eop_irq_funcs ; 
 int /*<<< orphan*/  gfx_v7_0_priv_inst_irq_funcs ; 
 int /*<<< orphan*/  gfx_v7_0_priv_reg_irq_funcs ; 

__attribute__((used)) static void gfx_v7_0_set_irq_funcs(struct amdgpu_device *adev)
{
	adev->gfx.eop_irq.num_types = AMDGPU_CP_IRQ_LAST;
	adev->gfx.eop_irq.funcs = &gfx_v7_0_eop_irq_funcs;

	adev->gfx.priv_reg_irq.num_types = 1;
	adev->gfx.priv_reg_irq.funcs = &gfx_v7_0_priv_reg_irq_funcs;

	adev->gfx.priv_inst_irq.num_types = 1;
	adev->gfx.priv_inst_irq.funcs = &gfx_v7_0_priv_inst_irq_funcs;
}