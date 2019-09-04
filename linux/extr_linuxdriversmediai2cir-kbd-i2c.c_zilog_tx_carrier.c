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
typedef  int u32 ;
struct rc_dev {struct IR_i2c* priv; } ;
struct IR_i2c {int carrier; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int zilog_tx_carrier(struct rc_dev *dev, u32 carrier)
{
	struct IR_i2c *ir = dev->priv;

	if (carrier > 500000 || carrier < 20000)
		return -EINVAL;

	ir->carrier = carrier;

	return 0;
}