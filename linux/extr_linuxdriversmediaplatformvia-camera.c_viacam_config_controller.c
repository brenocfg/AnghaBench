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
struct via_camera {int /*<<< orphan*/  flags; TYPE_1__* viadev; } ;
struct TYPE_2__ {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CF_CONFIG_NEEDED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int viacam_ctlr_cbufs (struct via_camera*) ; 
 int /*<<< orphan*/  viacam_ctlr_image (struct via_camera*) ; 

__attribute__((used)) static int viacam_config_controller(struct via_camera *cam)
{
	int ret;
	unsigned long flags;

	spin_lock_irqsave(&cam->viadev->reg_lock, flags);
	ret = viacam_ctlr_cbufs(cam);
	if (!ret)
		viacam_ctlr_image(cam);
	spin_unlock_irqrestore(&cam->viadev->reg_lock, flags);
	clear_bit(CF_CONFIG_NEEDED, &cam->flags);
	return ret;
}