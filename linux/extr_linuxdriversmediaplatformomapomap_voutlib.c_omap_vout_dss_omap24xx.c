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

/* Variables and functions */
 scalar_t__ OMAPDSS_VER_OMAP24xx ; 
 scalar_t__ omapdss_get_version () ; 

bool omap_vout_dss_omap24xx(void)
{
	return omapdss_get_version() == OMAPDSS_VER_OMAP24xx;
}