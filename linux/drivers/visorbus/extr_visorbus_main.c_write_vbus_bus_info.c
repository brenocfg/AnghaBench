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
struct visor_vbus_headerinfo {int bus_info_offset; } ;
struct visor_vbus_deviceinfo {int dummy; } ;
struct channel_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  visorchannel_write (struct visorchannel*,int,struct visor_vbus_deviceinfo*,int) ; 

__attribute__((used)) static void write_vbus_bus_info(struct visorchannel *chan,
				struct visor_vbus_headerinfo *hdr_info,
				struct visor_vbus_deviceinfo *info)
{
	int off;

	if (hdr_info->bus_info_offset == 0)
		return;

	off = sizeof(struct channel_header) + hdr_info->bus_info_offset;
	visorchannel_write(chan, off, info, sizeof(*info));
}