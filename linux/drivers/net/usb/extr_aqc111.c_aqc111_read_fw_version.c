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
struct usbnet {int dummy; } ;
struct TYPE_2__ {int major; int minor; int rev; } ;
struct aqc111_data {TYPE_1__ fw_ver; } ;

/* Variables and functions */
 int /*<<< orphan*/  AQ_ACCESS_MAC ; 
 int /*<<< orphan*/  AQ_FW_VER_MAJOR ; 
 int /*<<< orphan*/  AQ_FW_VER_MINOR ; 
 int /*<<< orphan*/  AQ_FW_VER_REV ; 
 int /*<<< orphan*/  aqc111_read_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*) ; 

__attribute__((used)) static void aqc111_read_fw_version(struct usbnet *dev,
				   struct aqc111_data *aqc111_data)
{
	aqc111_read_cmd(dev, AQ_ACCESS_MAC, AQ_FW_VER_MAJOR,
			1, 1, &aqc111_data->fw_ver.major);
	aqc111_read_cmd(dev, AQ_ACCESS_MAC, AQ_FW_VER_MINOR,
			1, 1, &aqc111_data->fw_ver.minor);
	aqc111_read_cmd(dev, AQ_ACCESS_MAC, AQ_FW_VER_REV,
			1, 1, &aqc111_data->fw_ver.rev);

	if (aqc111_data->fw_ver.major & 0x80)
		aqc111_data->fw_ver.major &= ~0x80;
}