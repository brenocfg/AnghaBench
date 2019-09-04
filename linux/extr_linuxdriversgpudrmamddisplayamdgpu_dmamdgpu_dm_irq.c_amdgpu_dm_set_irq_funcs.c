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
struct TYPE_6__ {int /*<<< orphan*/ * funcs; int /*<<< orphan*/  num_types; } ;
struct TYPE_7__ {int /*<<< orphan*/  num_hpd; int /*<<< orphan*/  num_crtc; } ;
struct TYPE_5__ {int /*<<< orphan*/ * funcs; int /*<<< orphan*/  num_types; } ;
struct TYPE_8__ {int /*<<< orphan*/ * funcs; int /*<<< orphan*/  num_types; } ;
struct amdgpu_device {TYPE_2__ hpd_irq; TYPE_3__ mode_info; TYPE_1__ pageflip_irq; TYPE_4__ crtc_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_crtc_irq_funcs ; 
 int /*<<< orphan*/  dm_hpd_irq_funcs ; 
 int /*<<< orphan*/  dm_pageflip_irq_funcs ; 

void amdgpu_dm_set_irq_funcs(struct amdgpu_device *adev)
{

	adev->crtc_irq.num_types = adev->mode_info.num_crtc;
	adev->crtc_irq.funcs = &dm_crtc_irq_funcs;

	adev->pageflip_irq.num_types = adev->mode_info.num_crtc;
	adev->pageflip_irq.funcs = &dm_pageflip_irq_funcs;

	adev->hpd_irq.num_types = adev->mode_info.num_hpd;
	adev->hpd_irq.funcs = &dm_hpd_irq_funcs;
}