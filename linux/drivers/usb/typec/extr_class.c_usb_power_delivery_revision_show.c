#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct typec_port {TYPE_1__* cap; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int pd_revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct typec_port* to_typec_port (struct device*) ; 

__attribute__((used)) static ssize_t usb_power_delivery_revision_show(struct device *dev,
						struct device_attribute *attr,
						char *buf)
{
	struct typec_port *p = to_typec_port(dev);

	return sprintf(buf, "%d\n", (p->cap->pd_revision >> 8) & 0xff);
}