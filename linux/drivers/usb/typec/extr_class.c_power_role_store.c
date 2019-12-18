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
struct typec_port {scalar_t__ pwr_opmode; size_t port_type; int /*<<< orphan*/  port_type_lock; TYPE_1__* cap; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int (* pr_set ) (TYPE_1__*,int) ;int /*<<< orphan*/  pd_revision; } ;

/* Variables and functions */
 int EIO ; 
 int EOPNOTSUPP ; 
 size_t TYPEC_PORT_DRP ; 
 scalar_t__ TYPEC_PWR_MODE_PD ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_1__*,int) ; 
 int sysfs_match_string (int /*<<< orphan*/ ,char const*) ; 
 struct typec_port* to_typec_port (struct device*) ; 
 int /*<<< orphan*/ * typec_port_power_roles ; 
 int /*<<< orphan*/  typec_roles ; 

__attribute__((used)) static ssize_t power_role_store(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t size)
{
	struct typec_port *port = to_typec_port(dev);
	int ret;

	if (!port->cap->pd_revision) {
		dev_dbg(dev, "USB Power Delivery not supported\n");
		return -EOPNOTSUPP;
	}

	if (!port->cap->pr_set) {
		dev_dbg(dev, "power role swapping not supported\n");
		return -EOPNOTSUPP;
	}

	if (port->pwr_opmode != TYPEC_PWR_MODE_PD) {
		dev_dbg(dev, "partner unable to swap power role\n");
		return -EIO;
	}

	ret = sysfs_match_string(typec_roles, buf);
	if (ret < 0)
		return ret;

	mutex_lock(&port->port_type_lock);
	if (port->port_type != TYPEC_PORT_DRP) {
		dev_dbg(dev, "port type fixed at \"%s\"",
			     typec_port_power_roles[port->port_type]);
		ret = -EOPNOTSUPP;
		goto unlock_and_ret;
	}

	ret = port->cap->pr_set(port->cap, ret);
	if (ret)
		goto unlock_and_ret;

	ret = size;
unlock_and_ret:
	mutex_unlock(&port->port_type_lock);
	return ret;
}