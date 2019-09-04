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
struct isp_device {int dummy; } ;

/* Variables and functions */
 struct isp_device* __omap3isp_get (struct isp_device*,int) ; 

struct isp_device *omap3isp_get(struct isp_device *isp)
{
	return __omap3isp_get(isp, true);
}