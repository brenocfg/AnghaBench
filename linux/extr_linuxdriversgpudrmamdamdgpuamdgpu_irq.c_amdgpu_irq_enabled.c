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
struct amdgpu_irq_src {unsigned int num_types; int /*<<< orphan*/ * enabled_types; TYPE_2__* funcs; } ;
struct amdgpu_device {TYPE_1__* ddev; } ;
struct TYPE_4__ {int /*<<< orphan*/  set; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 

bool amdgpu_irq_enabled(struct amdgpu_device *adev, struct amdgpu_irq_src *src,
			unsigned type)
{
	if (!adev->ddev->irq_enabled)
		return false;

	if (type >= src->num_types)
		return false;

	if (!src->enabled_types || !src->funcs->set)
		return false;

	return !!atomic_read(&src->enabled_types[type]);
}