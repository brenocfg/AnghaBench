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
struct device_connection {scalar_t__* endpoint; scalar_t__ fwnode; scalar_t__ id; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPROBE_DEFER ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct device* class_find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwnode_property_present (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  name_match ; 
 int /*<<< orphan*/  switch_fwnode_match ; 
 void* to_typec_switch (struct device*) ; 
 int /*<<< orphan*/  typec_mux_class ; 

__attribute__((used)) static void *typec_switch_match(struct device_connection *con, int ep,
				void *data)
{
	struct device *dev;

	if (con->fwnode) {
		if (con->id && !fwnode_property_present(con->fwnode, con->id))
			return NULL;

		dev = class_find_device(&typec_mux_class, NULL, con->fwnode,
					switch_fwnode_match);
	} else {
		dev = class_find_device(&typec_mux_class, NULL,
					con->endpoint[ep], name_match);
	}

	return dev ? to_typec_switch(dev) : ERR_PTR(-EPROBE_DEFER);
}