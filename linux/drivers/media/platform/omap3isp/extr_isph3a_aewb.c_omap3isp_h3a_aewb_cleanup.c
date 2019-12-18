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
struct isp_device {int /*<<< orphan*/  isp_aewb; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap3isp_stat_cleanup (int /*<<< orphan*/ *) ; 

void omap3isp_h3a_aewb_cleanup(struct isp_device *isp)
{
	omap3isp_stat_cleanup(&isp->isp_aewb);
}