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
struct amdgpu_iv_entry {int /*<<< orphan*/ * src_data; int /*<<< orphan*/  src_id; } ;
struct amdgpu_irq_src {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dc; } ;
struct amdgpu_device {TYPE_1__ dm; } ;
typedef  enum dc_irq_source { ____Placeholder_dc_irq_source } dc_irq_source ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_dm_irq_immediate_work (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  amdgpu_dm_irq_schedule_work (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  dc_interrupt_ack (int /*<<< orphan*/ ,int) ; 
 int dc_interrupt_to_irq_source (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amdgpu_dm_irq_handler(struct amdgpu_device *adev,
				 struct amdgpu_irq_src *source,
				 struct amdgpu_iv_entry *entry)
{

	enum dc_irq_source src =
		dc_interrupt_to_irq_source(
			adev->dm.dc,
			entry->src_id,
			entry->src_data[0]);

	dc_interrupt_ack(adev->dm.dc, src);

	/* Call high irq work immediately */
	amdgpu_dm_irq_immediate_work(adev, src);
	/*Schedule low_irq work */
	amdgpu_dm_irq_schedule_work(adev, src);

	return 0;
}