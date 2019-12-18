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
struct TYPE_2__ {int /*<<< orphan*/  ih; } ;
struct amdgpu_device {TYPE_1__ irq; } ;

/* Variables and functions */
 int amdgpu_ih_ring_init (struct amdgpu_device*,int /*<<< orphan*/ *,int,int) ; 
 int amdgpu_irq_init (struct amdgpu_device*) ; 

__attribute__((used)) static int cz_ih_sw_init(void *handle)
{
	int r;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	r = amdgpu_ih_ring_init(adev, &adev->irq.ih, 64 * 1024, false);
	if (r)
		return r;

	r = amdgpu_irq_init(adev);

	return r;
}