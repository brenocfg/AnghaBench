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
struct TYPE_2__ {scalar_t__ dev; } ;
struct amdgpu_device {TYPE_1__ kfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  kgd2kfd_interrupt (scalar_t__,void const*) ; 

void amdgpu_amdkfd_interrupt(struct amdgpu_device *adev,
		const void *ih_ring_entry)
{
	if (adev->kfd.dev)
		kgd2kfd_interrupt(adev->kfd.dev, ih_ring_entry);
}