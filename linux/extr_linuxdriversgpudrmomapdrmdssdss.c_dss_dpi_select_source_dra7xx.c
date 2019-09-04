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
struct dss_device {int dummy; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;

/* Variables and functions */
 int EINVAL ; 
 int OMAP_DSS_CHANNEL_LCD2 ; 
 int OMAP_DSS_CHANNEL_LCD3 ; 
 int dss_dpi_select_source_omap5 (struct dss_device*,int,int) ; 

__attribute__((used)) static int dss_dpi_select_source_dra7xx(struct dss_device *dss, int port,
					enum omap_channel channel)
{
	switch (port) {
	case 0:
		return dss_dpi_select_source_omap5(dss, port, channel);
	case 1:
		if (channel != OMAP_DSS_CHANNEL_LCD2)
			return -EINVAL;
		break;
	case 2:
		if (channel != OMAP_DSS_CHANNEL_LCD3)
			return -EINVAL;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}