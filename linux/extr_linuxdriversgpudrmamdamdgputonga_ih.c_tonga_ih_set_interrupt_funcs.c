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
struct TYPE_2__ {int /*<<< orphan*/ * ih_funcs; } ;
struct amdgpu_device {TYPE_1__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  tonga_ih_funcs ; 

__attribute__((used)) static void tonga_ih_set_interrupt_funcs(struct amdgpu_device *adev)
{
	if (adev->irq.ih_funcs == NULL)
		adev->irq.ih_funcs = &tonga_ih_funcs;
}