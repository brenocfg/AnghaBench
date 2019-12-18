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
struct isp_device {int /*<<< orphan*/  isp_res; } ;

/* Variables and functions */
 int omap3isp_resizer_busy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int isp_pipeline_wait_resizer(struct isp_device *isp)
{
	return omap3isp_resizer_busy(&isp->isp_res);
}