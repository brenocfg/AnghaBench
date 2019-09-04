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
struct solo_dev {int /*<<< orphan*/  i2c_wait; int /*<<< orphan*/  i2c_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  IIC_STATE_STOP ; 
 int /*<<< orphan*/  SOLO_IIC_CTRL ; 
 int /*<<< orphan*/  SOLO_IRQ_IIC ; 
 int /*<<< orphan*/  solo_irq_off (struct solo_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  solo_reg_write (struct solo_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void solo_i2c_stop(struct solo_dev *solo_dev)
{
	solo_irq_off(solo_dev, SOLO_IRQ_IIC);
	solo_reg_write(solo_dev, SOLO_IIC_CTRL, 0);
	solo_dev->i2c_state = IIC_STATE_STOP;
	wake_up(&solo_dev->i2c_wait);
}