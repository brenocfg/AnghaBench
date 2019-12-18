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
typedef  int /*<<< orphan*/  u32 ;
struct visor_vbus_headerinfo {int dummy; } ;
struct visor_vbus_deviceinfo {int dummy; } ;
struct visor_driver {int /*<<< orphan*/  name; TYPE_2__* channel_types; } ;
struct TYPE_3__ {int /*<<< orphan*/  driver; } ;
struct visor_device {int /*<<< orphan*/  visorchannel; int /*<<< orphan*/  channel_type_guid; TYPE_1__ device; scalar_t__ vbus_hdr_info; int /*<<< orphan*/  chipset_dev_no; int /*<<< orphan*/  chipset_bus_no; } ;
struct TYPE_4__ {char* name; int /*<<< orphan*/  guid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ROOT_DEVICE ; 
 int /*<<< orphan*/  bus_device_info_init (struct visor_vbus_deviceinfo*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chipset_driverinfo ; 
 int /*<<< orphan*/  clientbus_driverinfo ; 
 scalar_t__ guid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct visor_driver* to_visor_driver (int /*<<< orphan*/ ) ; 
 struct visor_device* visorbus_get_device_by_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_vbus_bus_info (int /*<<< orphan*/ ,struct visor_vbus_headerinfo*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_vbus_chp_info (int /*<<< orphan*/ ,struct visor_vbus_headerinfo*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_vbus_dev_info (int /*<<< orphan*/ ,struct visor_vbus_headerinfo*,struct visor_vbus_deviceinfo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void publish_vbus_dev_info(struct visor_device *visordev)
{
	int i;
	struct visor_device *bdev;
	struct visor_driver *visordrv;
	u32 bus_no = visordev->chipset_bus_no;
	u32 dev_no = visordev->chipset_dev_no;
	struct visor_vbus_deviceinfo dev_info;
	const char *chan_type_name = NULL;
	struct visor_vbus_headerinfo *hdr_info;

	if (!visordev->device.driver)
		return;
	bdev = visorbus_get_device_by_id(bus_no, BUS_ROOT_DEVICE, NULL);
	if (!bdev)
		return;
	hdr_info = (struct visor_vbus_headerinfo *)bdev->vbus_hdr_info;
	if (!hdr_info)
		return;
	visordrv = to_visor_driver(visordev->device.driver);

	/*
	 * Within the list of device types (by GUID) that the driver
	 * says it supports, find out which one of those types matches
	 * the type of this device, so that we can include the device
	 * type name
	 */
	for (i = 0; visordrv->channel_types[i].name; i++) {
		if (guid_equal(&visordrv->channel_types[i].guid,
			       &visordev->channel_type_guid)) {
			chan_type_name = visordrv->channel_types[i].name;
			break;
		}
	}
	bus_device_info_init(&dev_info, chan_type_name, visordrv->name);
	write_vbus_dev_info(bdev->visorchannel, hdr_info, &dev_info, dev_no);
	write_vbus_chp_info(bdev->visorchannel, hdr_info, &chipset_driverinfo);
	write_vbus_bus_info(bdev->visorchannel, hdr_info,
			    &clientbus_driverinfo);
}