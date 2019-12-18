#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rmi_device {TYPE_1__* driver; } ;
struct TYPE_2__ {int (* reset_handler ) (struct rmi_device*) ;} ;

/* Variables and functions */
 int stub1 (struct rmi_device*) ; 

__attribute__((used)) static inline int rmi_reset(struct rmi_device *d)
{
	return d->driver->reset_handler(d);
}