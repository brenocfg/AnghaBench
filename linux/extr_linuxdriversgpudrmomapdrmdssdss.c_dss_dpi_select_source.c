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
struct dss_device {TYPE_2__* feat; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* dpi_select_source ) (struct dss_device*,int,int) ;} ;

/* Variables and functions */
 int stub1 (struct dss_device*,int,int) ; 

int dss_dpi_select_source(struct dss_device *dss, int port,
			  enum omap_channel channel)
{
	return dss->feat->ops->dpi_select_source(dss, port, channel);
}