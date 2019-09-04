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
struct gnss_serial {TYPE_1__* ops; } ;
typedef  enum gnss_serial_pm_state { ____Placeholder_gnss_serial_pm_state } gnss_serial_pm_state ;
struct TYPE_2__ {int (* set_power ) (struct gnss_serial*,int) ;} ;

/* Variables and functions */
 int stub1 (struct gnss_serial*,int) ; 

__attribute__((used)) static int gnss_serial_set_power(struct gnss_serial *gserial,
					enum gnss_serial_pm_state state)
{
	if (!gserial->ops || !gserial->ops->set_power)
		return 0;

	return gserial->ops->set_power(gserial, state);
}