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
struct device_driver {int dummy; } ;
struct css_driver {int (* settle ) () ;} ;

/* Variables and functions */
 int stub1 () ; 
 struct css_driver* to_cssdriver (struct device_driver*) ; 

__attribute__((used)) static int css_settle(struct device_driver *drv, void *unused)
{
	struct css_driver *cssdrv = to_cssdriver(drv);

	if (cssdrv->settle)
		return cssdrv->settle();
	return 0;
}