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
struct xenbus_device {int /*<<< orphan*/  work; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ XS_LOCAL ; 
 struct xenbus_device* to_xenbus_device (struct device*) ; 
 scalar_t__ xen_store_domain_type ; 
 int xenbus_dev_probe (struct device*) ; 
 int /*<<< orphan*/  xenbus_frontend_delayed_resume ; 

__attribute__((used)) static int xenbus_frontend_dev_probe(struct device *dev)
{
	if (xen_store_domain_type == XS_LOCAL) {
		struct xenbus_device *xdev = to_xenbus_device(dev);
		INIT_WORK(&xdev->work, xenbus_frontend_delayed_resume);
	}

	return xenbus_dev_probe(dev);
}