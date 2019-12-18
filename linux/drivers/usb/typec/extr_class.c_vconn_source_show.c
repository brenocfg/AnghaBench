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
struct typec_port {scalar_t__ vconn_role; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ TYPEC_SOURCE ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct typec_port* to_typec_port (struct device*) ; 

__attribute__((used)) static ssize_t vconn_source_show(struct device *dev,
				 struct device_attribute *attr, char *buf)
{
	struct typec_port *port = to_typec_port(dev);

	return sprintf(buf, "%s\n",
		       port->vconn_role == TYPEC_SOURCE ? "yes" : "no");
}