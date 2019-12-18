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
struct TYPE_7__ {int /*<<< orphan*/ * funcs; int /*<<< orphan*/  num_types; } ;
struct TYPE_8__ {scalar_t__ num_crtc; int /*<<< orphan*/  num_hpd; } ;
struct TYPE_6__ {scalar_t__ num_types; int /*<<< orphan*/ * funcs; } ;
struct TYPE_5__ {scalar_t__ num_types; int /*<<< orphan*/ * funcs; } ;
struct amdgpu_device {TYPE_3__ hpd_irq; TYPE_4__ mode_info; TYPE_2__ pageflip_irq; TYPE_1__ crtc_irq; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_CRTC_IRQ_VLINE1 ; 
 int /*<<< orphan*/  dce_v6_0_crtc_irq_funcs ; 
 int /*<<< orphan*/  dce_v6_0_hpd_irq_funcs ; 
 int /*<<< orphan*/  dce_v6_0_pageflip_irq_funcs ; 

__attribute__((used)) static void dce_v6_0_set_irq_funcs(struct amdgpu_device *adev)
{
	if (adev->mode_info.num_crtc > 0)
		adev->crtc_irq.num_types = AMDGPU_CRTC_IRQ_VLINE1 + adev->mode_info.num_crtc;
	else
		adev->crtc_irq.num_types = 0;
	adev->crtc_irq.funcs = &dce_v6_0_crtc_irq_funcs;

	adev->pageflip_irq.num_types = adev->mode_info.num_crtc;
	adev->pageflip_irq.funcs = &dce_v6_0_pageflip_irq_funcs;

	adev->hpd_irq.num_types = adev->mode_info.num_hpd;
	adev->hpd_irq.funcs = &dce_v6_0_hpd_irq_funcs;
}