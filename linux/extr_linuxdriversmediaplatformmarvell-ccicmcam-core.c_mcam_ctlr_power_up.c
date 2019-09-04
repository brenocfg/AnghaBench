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
struct mcam_camera {int (* plat_power_up ) (struct mcam_camera*) ;int /*<<< orphan*/  dev_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  C1_PWRDWN ; 
 int /*<<< orphan*/  REG_CTRL1 ; 
 int /*<<< orphan*/  mcam_reg_clear_bit (struct mcam_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct mcam_camera*) ; 

__attribute__((used)) static int mcam_ctlr_power_up(struct mcam_camera *cam)
{
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&cam->dev_lock, flags);
	ret = cam->plat_power_up(cam);
	if (ret) {
		spin_unlock_irqrestore(&cam->dev_lock, flags);
		return ret;
	}
	mcam_reg_clear_bit(cam, REG_CTRL1, C1_PWRDWN);
	spin_unlock_irqrestore(&cam->dev_lock, flags);
	msleep(5); /* Just to be sure */
	return 0;
}