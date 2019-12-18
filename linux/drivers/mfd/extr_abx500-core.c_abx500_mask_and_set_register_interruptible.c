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
typedef  int /*<<< orphan*/  u8 ;
struct device {int /*<<< orphan*/  parent; } ;
struct abx500_ops {int (* mask_and_set_register ) (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  lookup_ops (int /*<<< orphan*/ ,struct abx500_ops**) ; 
 int stub1 (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int abx500_mask_and_set_register_interruptible(struct device *dev, u8 bank,
	u8 reg, u8 bitmask, u8 bitvalues)
{
	struct abx500_ops *ops;

	lookup_ops(dev->parent, &ops);
	if (ops && ops->mask_and_set_register)
		return ops->mask_and_set_register(dev, bank,
			reg, bitmask, bitvalues);
	else
		return -ENOTSUPP;
}