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
struct TYPE_2__ {int /*<<< orphan*/ * domain; } ;
struct amdgpu_device {TYPE_1__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ *) ; 

void amdgpu_irq_remove_domain(struct amdgpu_device *adev)
{
	if (adev->irq.domain) {
		irq_domain_remove(adev->irq.domain);
		adev->irq.domain = NULL;
	}
}