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
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;
struct TYPE_4__ {TYPE_1__* feat; } ;
struct TYPE_3__ {int (* dpi_select_source ) (int,int) ;} ;

/* Variables and functions */
 TYPE_2__ dss ; 
 int stub1 (int,int) ; 

int dss_dpi_select_source(int port, enum omap_channel channel)
{
	return dss.feat->dpi_select_source(port, channel);
}