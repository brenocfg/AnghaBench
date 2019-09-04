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
typedef  int /*<<< orphan*/  u32 ;
struct rc_dev {struct ir_rx51* priv; } ;
struct ir_rx51 {int /*<<< orphan*/  duty_cycle; } ;

/* Variables and functions */

__attribute__((used)) static int ir_rx51_set_duty_cycle(struct rc_dev *dev, u32 duty)
{
	struct ir_rx51 *ir_rx51 = dev->priv;

	ir_rx51->duty_cycle = duty;

	return 0;
}