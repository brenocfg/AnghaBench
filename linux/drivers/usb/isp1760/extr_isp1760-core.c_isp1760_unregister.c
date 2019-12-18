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
struct isp1760_device {int /*<<< orphan*/  hcd; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct isp1760_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  isp1760_hcd_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isp1760_udc_unregister (struct isp1760_device*) ; 

void isp1760_unregister(struct device *dev)
{
	struct isp1760_device *isp = dev_get_drvdata(dev);

	isp1760_udc_unregister(isp);
	isp1760_hcd_unregister(&isp->hcd);
}