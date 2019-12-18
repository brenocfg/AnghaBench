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
struct typec_port {int port_type; int /*<<< orphan*/  port_type_lock; TYPE_1__* cap; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  enum typec_port_type { ____Placeholder_typec_port_type } typec_port_type ;
struct TYPE_2__ {int (* port_type_set ) (TYPE_1__*,int) ;scalar_t__ type; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ TYPEC_PORT_DRP ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_1__*,int) ; 
 int sysfs_match_string (int /*<<< orphan*/ ,char const*) ; 
 struct typec_port* to_typec_port (struct device*) ; 
 int /*<<< orphan*/  typec_port_power_roles ; 

__attribute__((used)) static ssize_t
port_type_store(struct device *dev, struct device_attribute *attr,
			const char *buf, size_t size)
{
	struct typec_port *port = to_typec_port(dev);
	int ret;
	enum typec_port_type type;

	if (!port->cap->port_type_set || port->cap->type != TYPEC_PORT_DRP) {
		dev_dbg(dev, "changing port type not supported\n");
		return -EOPNOTSUPP;
	}

	ret = sysfs_match_string(typec_port_power_roles, buf);
	if (ret < 0)
		return ret;

	type = ret;
	mutex_lock(&port->port_type_lock);

	if (port->port_type == type) {
		ret = size;
		goto unlock_and_ret;
	}

	ret = port->cap->port_type_set(port->cap, type);
	if (ret)
		goto unlock_and_ret;

	port->port_type = type;
	ret = size;

unlock_and_ret:
	mutex_unlock(&port->port_type_lock);
	return ret;
}