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
struct rmi_device {int dummy; } ;

/* Variables and functions */
 int rmi_driver_process_config_requests (struct rmi_device*) ; 
 int rmi_process_interrupt_requests (struct rmi_device*) ; 

int rmi_enable_sensor(struct rmi_device *rmi_dev)
{
	int retval = 0;

	retval = rmi_driver_process_config_requests(rmi_dev);
	if (retval < 0)
		return retval;

	return rmi_process_interrupt_requests(rmi_dev);
}