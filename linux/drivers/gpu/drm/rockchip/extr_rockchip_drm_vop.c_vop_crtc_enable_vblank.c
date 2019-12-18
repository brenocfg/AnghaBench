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
struct vop {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  is_enabled; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  FS_INTR ; 
 int /*<<< orphan*/  VOP_INTR_SET_TYPE (struct vop*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  clear ; 
 int /*<<< orphan*/  enable ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vop* to_vop (struct drm_crtc*) ; 

__attribute__((used)) static int vop_crtc_enable_vblank(struct drm_crtc *crtc)
{
	struct vop *vop = to_vop(crtc);
	unsigned long flags;

	if (WARN_ON(!vop->is_enabled))
		return -EPERM;

	spin_lock_irqsave(&vop->irq_lock, flags);

	VOP_INTR_SET_TYPE(vop, clear, FS_INTR, 1);
	VOP_INTR_SET_TYPE(vop, enable, FS_INTR, 1);

	spin_unlock_irqrestore(&vop->irq_lock, flags);

	return 0;
}