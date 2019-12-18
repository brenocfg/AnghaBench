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
struct vcc_port {int /*<<< orphan*/  domain; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct vcc_port* dev_get_drvdata (struct device*) ; 
 int scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t vcc_sysfs_domain_show(struct device *dev,
				     struct device_attribute *attr,
				     char *buf)
{
	struct vcc_port *port;
	int rv;

	port = dev_get_drvdata(dev);
	if (!port)
		return -ENODEV;

	rv = scnprintf(buf, PAGE_SIZE, "%s\n", port->domain);

	return rv;
}