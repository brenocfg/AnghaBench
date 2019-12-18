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
typedef  int /*<<< orphan*/  visorbus_state_complete_func ;
struct visornic_devdata {int dummy; } ;
struct visor_device {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 struct visornic_devdata* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  visornic_serverdown (struct visornic_devdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int visornic_pause(struct visor_device *dev,
			  visorbus_state_complete_func complete_func)
{
	struct visornic_devdata *devdata = dev_get_drvdata(&dev->device);

	visornic_serverdown(devdata, complete_func);
	return 0;
}