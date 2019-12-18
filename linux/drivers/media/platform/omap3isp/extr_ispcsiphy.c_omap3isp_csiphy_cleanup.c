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
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; } ;
struct isp_device {TYPE_2__ isp_csiphy2; TYPE_1__ isp_csiphy1; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

void omap3isp_csiphy_cleanup(struct isp_device *isp)
{
	mutex_destroy(&isp->isp_csiphy1.mutex);
	mutex_destroy(&isp->isp_csiphy2.mutex);
}