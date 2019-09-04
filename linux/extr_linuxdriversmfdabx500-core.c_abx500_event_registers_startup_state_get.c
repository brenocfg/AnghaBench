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
struct abx500_ops {int (* event_registers_startup_state_get ) (struct device*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  lookup_ops (int /*<<< orphan*/ ,struct abx500_ops**) ; 
 int stub1 (struct device*,int /*<<< orphan*/ *) ; 

int abx500_event_registers_startup_state_get(struct device *dev, u8 *event)
{
	struct abx500_ops *ops;

	lookup_ops(dev->parent, &ops);
	if (ops && ops->event_registers_startup_state_get)
		return ops->event_registers_startup_state_get(dev, event);
	else
		return -ENOTSUPP;
}