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
struct vop {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 int readx_poll_timeout_atomic (int /*<<< orphan*/ ,struct vop*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vop_fs_irq_is_pending ; 

__attribute__((used)) static void vop_wait_for_irq_handler(struct vop *vop)
{
	bool pending;
	int ret;

	/*
	 * Spin until frame start interrupt status bit goes low, which means
	 * that interrupt handler was invoked and cleared it. The timeout of
	 * 10 msecs is really too long, but it is just a safety measure if
	 * something goes really wrong. The wait will only happen in the very
	 * unlikely case of a vblank happening exactly at the same time and
	 * shouldn't exceed microseconds range.
	 */
	ret = readx_poll_timeout_atomic(vop_fs_irq_is_pending, vop, pending,
					!pending, 0, 10 * 1000);
	if (ret)
		DRM_DEV_ERROR(vop->dev, "VOP vblank IRQ stuck for 10 ms\n");

	synchronize_irq(vop->irq);
}