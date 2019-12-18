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
struct ishtp_device {int fw_client_presentation_num; TYPE_2__* fw_clients; } ;
struct ishtp_cl_device {int dummy; } ;
typedef  int /*<<< orphan*/  guid_t ;
struct TYPE_3__ {int /*<<< orphan*/  protocol_name; } ;
struct TYPE_4__ {TYPE_1__ props; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ishtp_cl_device* ishtp_bus_add_device (struct ishtp_device*,int /*<<< orphan*/ ,char*) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (char*) ; 

int ishtp_bus_new_client(struct ishtp_device *dev)
{
	int	i;
	char	*dev_name;
	struct ishtp_cl_device	*cl_device;
	guid_t	device_uuid;

	/*
	 * For all reported clients, create an unconnected client and add its
	 * device to ISHTP bus.
	 * If appropriate driver has loaded, this will trigger its probe().
	 * Otherwise, probe() will be called when driver is loaded
	 */
	i = dev->fw_client_presentation_num - 1;
	device_uuid = dev->fw_clients[i].props.protocol_name;
	dev_name = kasprintf(GFP_KERNEL, "{%pUL}", &device_uuid);
	if (!dev_name)
		return	-ENOMEM;

	cl_device = ishtp_bus_add_device(dev, device_uuid, dev_name);
	if (!cl_device) {
		kfree(dev_name);
		return	-ENOENT;
	}

	kfree(dev_name);

	return	0;
}