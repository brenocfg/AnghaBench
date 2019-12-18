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
typedef  void* u32 ;
struct fixed_phy_status {int link; void* asym_pause; void* pause; void* speed; void* duplex; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (void**) ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  PHY_POLL ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixed_phy_register (int /*<<< orphan*/ ,struct fixed_phy_status*,struct device_node*) ; 
 struct device_node* of_get_child_by_name (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 void* of_property_read_bool (struct device_node*,char*) ; 
 scalar_t__ of_property_read_string (struct device_node*,char*,char const**) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,void**) ; 
 scalar_t__ of_property_read_u32_array (struct device_node*,char*,void**,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

int of_phy_register_fixed_link(struct device_node *np)
{
	struct fixed_phy_status status = {};
	struct device_node *fixed_link_node;
	u32 fixed_link_prop[5];
	const char *managed;

	if (of_property_read_string(np, "managed", &managed) == 0 &&
	    strcmp(managed, "in-band-status") == 0) {
		/* status is zeroed, namely its .link member */
		goto register_phy;
	}

	/* New binding */
	fixed_link_node = of_get_child_by_name(np, "fixed-link");
	if (fixed_link_node) {
		status.link = 1;
		status.duplex = of_property_read_bool(fixed_link_node,
						      "full-duplex");
		if (of_property_read_u32(fixed_link_node, "speed",
					 &status.speed)) {
			of_node_put(fixed_link_node);
			return -EINVAL;
		}
		status.pause = of_property_read_bool(fixed_link_node, "pause");
		status.asym_pause = of_property_read_bool(fixed_link_node,
							  "asym-pause");
		of_node_put(fixed_link_node);

		goto register_phy;
	}

	/* Old binding */
	if (of_property_read_u32_array(np, "fixed-link", fixed_link_prop,
				       ARRAY_SIZE(fixed_link_prop)) == 0) {
		status.link = 1;
		status.duplex = fixed_link_prop[1];
		status.speed  = fixed_link_prop[2];
		status.pause  = fixed_link_prop[3];
		status.asym_pause = fixed_link_prop[4];
		goto register_phy;
	}

	return -ENODEV;

register_phy:
	return PTR_ERR_OR_ZERO(fixed_phy_register(PHY_POLL, &status, np));
}