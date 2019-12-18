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
typedef  scalar_t__ u16 ;
struct typec_altmode_desc {scalar_t__ svid; } ;
struct device_connection {int /*<<< orphan*/  fwnode; int /*<<< orphan*/  id; int /*<<< orphan*/ * endpoint; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 void* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct device* class_find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fwnode_property_count_u16 (int /*<<< orphan*/ ,char*) ; 
 int fwnode_property_present (int /*<<< orphan*/ ,char*) ; 
 int fwnode_property_read_u16_array (int /*<<< orphan*/ ,char*,scalar_t__*,int) ; 
 scalar_t__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 int /*<<< orphan*/  mux_fwnode_match ; 
 int /*<<< orphan*/  name_match ; 
 void* to_typec_switch (struct device*) ; 
 int /*<<< orphan*/  typec_mux_class ; 

__attribute__((used)) static void *typec_mux_match(struct device_connection *con, int ep, void *data)
{
	const struct typec_altmode_desc *desc = data;
	struct device *dev;
	bool match;
	int nval;
	u16 *val;
	int i;

	if (!con->fwnode) {
		dev = class_find_device(&typec_mux_class, NULL,
					con->endpoint[ep], name_match);

		return dev ? to_typec_switch(dev) : ERR_PTR(-EPROBE_DEFER);
	}

	/*
	 * Check has the identifier already been "consumed". If it
	 * has, no need to do any extra connection identification.
	 */
	match = !con->id;
	if (match)
		goto find_mux;

	/* Accessory Mode muxes */
	if (!desc) {
		match = fwnode_property_present(con->fwnode, "accessory");
		if (match)
			goto find_mux;
		return NULL;
	}

	/* Alternate Mode muxes */
	nval = fwnode_property_count_u16(con->fwnode, "svid");
	if (nval <= 0)
		return NULL;

	val = kcalloc(nval, sizeof(*val), GFP_KERNEL);
	if (!val)
		return ERR_PTR(-ENOMEM);

	nval = fwnode_property_read_u16_array(con->fwnode, "svid", val, nval);
	if (nval < 0) {
		kfree(val);
		return ERR_PTR(nval);
	}

	for (i = 0; i < nval; i++) {
		match = val[i] == desc->svid;
		if (match) {
			kfree(val);
			goto find_mux;
		}
	}
	kfree(val);
	return NULL;

find_mux:
	dev = class_find_device(&typec_mux_class, NULL, con->fwnode,
				mux_fwnode_match);

	return dev ? to_typec_switch(dev) : ERR_PTR(-EPROBE_DEFER);
}