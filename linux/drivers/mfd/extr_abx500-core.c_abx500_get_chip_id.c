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
struct device {int /*<<< orphan*/  parent; } ;
struct abx500_ops {int (* get_chip_id ) (struct device*) ;} ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  lookup_ops (int /*<<< orphan*/ ,struct abx500_ops**) ; 
 int stub1 (struct device*) ; 

int abx500_get_chip_id(struct device *dev)
{
	struct abx500_ops *ops;

	lookup_ops(dev->parent, &ops);
	if (ops && ops->get_chip_id)
		return ops->get_chip_id(dev);
	else
		return -ENOTSUPP;
}