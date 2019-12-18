#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct kfd_dev {int /*<<< orphan*/  kgd; int /*<<< orphan*/  compute_profile; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_amdkfd_set_compute_idle (int /*<<< orphan*/ ,int) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 

void kfd_inc_compute_active(struct kfd_dev *kfd)
{
	if (atomic_inc_return(&kfd->compute_profile) == 1)
		amdgpu_amdkfd_set_compute_idle(kfd->kgd, false);
}