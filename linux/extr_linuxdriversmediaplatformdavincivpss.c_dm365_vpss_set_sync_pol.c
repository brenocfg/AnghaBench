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
struct vpss_sync_pol {int ccdpg_hdpol; int ccdpg_vdpol; } ;

/* Variables and functions */
 int DM365_CCDC_PG_HD_POL_SHIFT ; 
 int DM365_CCDC_PG_VD_POL_SHIFT ; 
 int /*<<< orphan*/  DM365_ISP5_CCDCMUX ; 
 int isp5_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp5_write (int,int /*<<< orphan*/ ) ; 

void dm365_vpss_set_sync_pol(struct vpss_sync_pol sync)
{
	int val = 0;
	val = isp5_read(DM365_ISP5_CCDCMUX);

	val |= (sync.ccdpg_hdpol << DM365_CCDC_PG_HD_POL_SHIFT);
	val |= (sync.ccdpg_vdpol << DM365_CCDC_PG_VD_POL_SHIFT);

	isp5_write(val, DM365_ISP5_CCDCMUX);
}