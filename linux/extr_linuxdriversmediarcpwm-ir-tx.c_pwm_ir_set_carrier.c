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
typedef  scalar_t__ u32 ;
struct rc_dev {struct pwm_ir* priv; } ;
struct pwm_ir {scalar_t__ carrier; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int pwm_ir_set_carrier(struct rc_dev *dev, u32 carrier)
{
	struct pwm_ir *pwm_ir = dev->priv;

	if (!carrier)
		return -EINVAL;

	pwm_ir->carrier = carrier;

	return 0;
}