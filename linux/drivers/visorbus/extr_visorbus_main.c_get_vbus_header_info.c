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
struct visorchannel {int dummy; } ;
struct visor_vbus_headerinfo {int struct_bytes; int device_info_struct_bytes; } ;
struct visor_vbus_deviceinfo {int dummy; } ;
struct visor_vbus_channel {int dummy; } ;
struct device {int dummy; } ;
struct channel_header {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  VISOR_CHANNEL_SIGNATURE ; 
 int /*<<< orphan*/  VISOR_VBUS_CHANNEL_VERSIONID ; 
 int /*<<< orphan*/  visor_check_channel (int /*<<< orphan*/ ,struct device*,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  visor_vbus_channel_guid ; 
 int /*<<< orphan*/  visorchannel_get_header (struct visorchannel*) ; 
 int visorchannel_read (struct visorchannel*,int,struct visor_vbus_headerinfo*,int) ; 

__attribute__((used)) static int get_vbus_header_info(struct visorchannel *chan,
				struct device *dev,
				struct visor_vbus_headerinfo *hdr_info)
{
	int err;

	if (!visor_check_channel(visorchannel_get_header(chan),
				 dev,
				 &visor_vbus_channel_guid,
				 "vbus",
				 sizeof(struct visor_vbus_channel),
				 VISOR_VBUS_CHANNEL_VERSIONID,
				 VISOR_CHANNEL_SIGNATURE))
		return -EINVAL;

	err = visorchannel_read(chan, sizeof(struct channel_header), hdr_info,
				sizeof(*hdr_info));
	if (err < 0)
		return err;
	if (hdr_info->struct_bytes < sizeof(struct visor_vbus_headerinfo))
		return -EINVAL;
	if (hdr_info->device_info_struct_bytes <
	    sizeof(struct visor_vbus_deviceinfo))
		return -EINVAL;
	return 0;
}