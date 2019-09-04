#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int num_types; int /*<<< orphan*/ * funcs; } ;
struct TYPE_14__ {int num_types; int /*<<< orphan*/ * funcs; } ;
struct TYPE_12__ {int /*<<< orphan*/ * funcs; int /*<<< orphan*/  num_types; } ;
struct TYPE_13__ {TYPE_4__ irq; } ;
struct TYPE_11__ {int num_types; int /*<<< orphan*/ * funcs; } ;
struct TYPE_10__ {int num_types; int /*<<< orphan*/ * funcs; } ;
struct TYPE_9__ {int /*<<< orphan*/ * funcs; int /*<<< orphan*/  num_types; } ;
struct TYPE_16__ {TYPE_7__ sq_irq; TYPE_6__ cp_ecc_error_irq; TYPE_5__ kiq; TYPE_3__ priv_inst_irq; TYPE_2__ priv_reg_irq; TYPE_1__ eop_irq; } ;
struct amdgpu_device {TYPE_8__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_CP_IRQ_LAST ; 
 int /*<<< orphan*/  AMDGPU_CP_KIQ_IRQ_LAST ; 
 int /*<<< orphan*/  gfx_v8_0_cp_ecc_error_irq_funcs ; 
 int /*<<< orphan*/  gfx_v8_0_eop_irq_funcs ; 
 int /*<<< orphan*/  gfx_v8_0_kiq_irq_funcs ; 
 int /*<<< orphan*/  gfx_v8_0_priv_inst_irq_funcs ; 
 int /*<<< orphan*/  gfx_v8_0_priv_reg_irq_funcs ; 
 int /*<<< orphan*/  gfx_v8_0_sq_irq_funcs ; 

__attribute__((used)) static void gfx_v8_0_set_irq_funcs(struct amdgpu_device *adev)
{
	adev->gfx.eop_irq.num_types = AMDGPU_CP_IRQ_LAST;
	adev->gfx.eop_irq.funcs = &gfx_v8_0_eop_irq_funcs;

	adev->gfx.priv_reg_irq.num_types = 1;
	adev->gfx.priv_reg_irq.funcs = &gfx_v8_0_priv_reg_irq_funcs;

	adev->gfx.priv_inst_irq.num_types = 1;
	adev->gfx.priv_inst_irq.funcs = &gfx_v8_0_priv_inst_irq_funcs;

	adev->gfx.kiq.irq.num_types = AMDGPU_CP_KIQ_IRQ_LAST;
	adev->gfx.kiq.irq.funcs = &gfx_v8_0_kiq_irq_funcs;

	adev->gfx.cp_ecc_error_irq.num_types = 1;
	adev->gfx.cp_ecc_error_irq.funcs = &gfx_v8_0_cp_ecc_error_irq_funcs;

	adev->gfx.sq_irq.num_types = 1;
	adev->gfx.sq_irq.funcs = &gfx_v8_0_sq_irq_funcs;
}