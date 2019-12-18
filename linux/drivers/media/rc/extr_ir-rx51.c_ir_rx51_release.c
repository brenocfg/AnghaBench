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
struct rc_dev {struct ir_rx51* priv; } ;
struct ir_rx51 {int /*<<< orphan*/  device_is_open; int /*<<< orphan*/  pwm; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ir_rx51_off (struct ir_rx51*) ; 
 int /*<<< orphan*/  pwm_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ir_rx51_release(struct rc_dev *dev)
{
	struct ir_rx51 *ir_rx51 = dev->priv;

	hrtimer_cancel(&ir_rx51->timer);
	ir_rx51_off(ir_rx51);
	pwm_put(ir_rx51->pwm);

	clear_bit(1, &ir_rx51->device_is_open);
}