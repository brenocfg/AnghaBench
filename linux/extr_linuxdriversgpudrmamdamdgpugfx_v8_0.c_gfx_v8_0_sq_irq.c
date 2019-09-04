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
struct amdgpu_iv_entry {unsigned int* src_data; } ;
struct amdgpu_irq_src {int dummy; } ;
struct TYPE_4__ {unsigned int ih_data; int /*<<< orphan*/  work; } ;
struct TYPE_3__ {TYPE_2__ sq_work; } ;
struct amdgpu_device {TYPE_1__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  gfx_v8_0_parse_sq_irq (struct amdgpu_device*,unsigned int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ work_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gfx_v8_0_sq_irq(struct amdgpu_device *adev,
			   struct amdgpu_irq_src *source,
			   struct amdgpu_iv_entry *entry)
{
	unsigned ih_data = entry->src_data[0];

	/*
	 * Try to submit work so SQ_EDC_INFO can be accessed from
	 * BH. If previous work submission hasn't finished yet
	 * just print whatever info is possible directly from the ISR.
	 */
	if (work_pending(&adev->gfx.sq_work.work)) {
		gfx_v8_0_parse_sq_irq(adev, ih_data);
	} else {
		adev->gfx.sq_work.ih_data = ih_data;
		schedule_work(&adev->gfx.sq_work.work);
	}

	return 0;
}