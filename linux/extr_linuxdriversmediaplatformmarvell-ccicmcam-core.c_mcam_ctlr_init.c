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
struct mcam_camera {int /*<<< orphan*/  dev_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  C0_ENABLE ; 
 int /*<<< orphan*/  C1_PWRDWN ; 
 int /*<<< orphan*/  CLK_DIV_MASK ; 
 int /*<<< orphan*/  REG_CLKCTRL ; 
 int /*<<< orphan*/  REG_CTRL0 ; 
 int /*<<< orphan*/  REG_CTRL1 ; 
 int /*<<< orphan*/  mcam_reg_clear_bit (struct mcam_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcam_reg_write_mask (struct mcam_camera*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mcam_ctlr_init(struct mcam_camera *cam)
{
	unsigned long flags;

	spin_lock_irqsave(&cam->dev_lock, flags);
	/*
	 * Make sure it's not powered down.
	 */
	mcam_reg_clear_bit(cam, REG_CTRL1, C1_PWRDWN);
	/*
	 * Turn off the enable bit.  It sure should be off anyway,
	 * but it's good to be sure.
	 */
	mcam_reg_clear_bit(cam, REG_CTRL0, C0_ENABLE);
	/*
	 * Clock the sensor appropriately.  Controller clock should
	 * be 48MHz, sensor "typical" value is half that.
	 */
	mcam_reg_write_mask(cam, REG_CLKCTRL, 2, CLK_DIV_MASK);
	spin_unlock_irqrestore(&cam->dev_lock, flags);
}