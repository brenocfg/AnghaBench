#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ type; } ;
union ioctl_arg {TYPE_2__ initiate_bus_reset; } ;
struct client {TYPE_1__* device; } ;
struct TYPE_3__ {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 scalar_t__ FW_CDEV_SHORT_RESET ; 
 int /*<<< orphan*/  fw_schedule_bus_reset (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int ioctl_initiate_bus_reset(struct client *client, union ioctl_arg *arg)
{
	fw_schedule_bus_reset(client->device->card, true,
			arg->initiate_bus_reset.type == FW_CDEV_SHORT_RESET);
	return 0;
}