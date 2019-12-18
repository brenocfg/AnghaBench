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
struct device_connection {int /*<<< orphan*/ * endpoint; scalar_t__ fwnode; } ;
typedef  void device ;

/* Variables and functions */
 int /*<<< orphan*/  EPROBE_DEFER ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 void* class_find_device_by_fwnode (int /*<<< orphan*/ ,scalar_t__) ; 
 void* class_find_device_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typec_class ; 

__attribute__((used)) static void *typec_port_match(struct device_connection *con, int ep, void *data)
{
	struct device *dev;

	/*
	 * FIXME: Check does the fwnode supports the requested SVID. If it does
	 * we need to return ERR_PTR(-PROBE_DEFER) when there is no device.
	 */
	if (con->fwnode)
		return class_find_device_by_fwnode(typec_class, con->fwnode);

	dev = class_find_device_by_name(typec_class, con->endpoint[ep]);

	return dev ? dev : ERR_PTR(-EPROBE_DEFER);
}