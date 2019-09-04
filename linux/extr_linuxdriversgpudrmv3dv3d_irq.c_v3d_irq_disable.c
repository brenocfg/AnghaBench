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
struct v3d_dev {int cores; int /*<<< orphan*/  overflow_mem_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  V3D_CORE_IRQS ; 
 int /*<<< orphan*/  V3D_CORE_WRITE (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V3D_CTL_INT_CLR ; 
 int /*<<< orphan*/  V3D_CTL_INT_MSK_SET ; 
 int /*<<< orphan*/  V3D_HUB_INT_CLR ; 
 int /*<<< orphan*/  V3D_HUB_INT_MSK_SET ; 
 int /*<<< orphan*/  V3D_HUB_IRQS ; 
 int /*<<< orphan*/  V3D_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 

void
v3d_irq_disable(struct v3d_dev *v3d)
{
	int core;

	/* Disable all interrupts. */
	for (core = 0; core < v3d->cores; core++)
		V3D_CORE_WRITE(core, V3D_CTL_INT_MSK_SET, ~0);
	V3D_WRITE(V3D_HUB_INT_MSK_SET, ~0);

	/* Clear any pending interrupts we might have left. */
	for (core = 0; core < v3d->cores; core++)
		V3D_CORE_WRITE(core, V3D_CTL_INT_CLR, V3D_CORE_IRQS);
	V3D_WRITE(V3D_HUB_INT_CLR, V3D_HUB_IRQS);

	cancel_work_sync(&v3d->overflow_mem_work);
}