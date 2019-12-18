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
struct device {int dummy; } ;
struct cdns3 {int role; } ;
typedef  enum usb_role { ____Placeholder_usb_role } usb_role ;

/* Variables and functions */
 struct cdns3* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static enum usb_role cdns3_role_get(struct device *dev)
{
	struct cdns3 *cdns = dev_get_drvdata(dev);

	return cdns->role;
}