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
typedef  int u32 ;
struct TYPE_2__ {int data; int type; int /*<<< orphan*/  prefer_role; } ;
struct tcpm_port {scalar_t__ port_type; int operating_snk_mw; int /*<<< orphan*/  self_powered; void* nr_snk_pdo; int /*<<< orphan*/  snk_pdo; TYPE_1__ typec_caps; void* nr_src_pdo; int /*<<< orphan*/  src_pdo; } ;
struct fwnode_handle {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PDO_MAX_OBJECTS ; 
 scalar_t__ TYPEC_PORT_SNK ; 
 scalar_t__ TYPEC_PORT_SRC ; 
 int fwnode_property_count_u32 (struct fwnode_handle*,char*) ; 
 int /*<<< orphan*/  fwnode_property_read_bool (struct fwnode_handle*,char*) ; 
 int fwnode_property_read_string (struct fwnode_handle*,char*,char const**) ; 
 scalar_t__ fwnode_property_read_u32 (struct fwnode_handle*,char*,int*) ; 
 int fwnode_property_read_u32_array (struct fwnode_handle*,char*,int /*<<< orphan*/ ,void*) ; 
 void* min (int,int /*<<< orphan*/ ) ; 
 scalar_t__ tcpm_validate_caps (struct tcpm_port*,int /*<<< orphan*/ ,void*) ; 
 int typec_find_port_data_role (char const*) ; 
 int typec_find_port_power_role (char const*) ; 
 int /*<<< orphan*/  typec_find_power_role (char const*) ; 

__attribute__((used)) static int tcpm_fw_get_caps(struct tcpm_port *port,
			    struct fwnode_handle *fwnode)
{
	const char *cap_str;
	int ret;
	u32 mw;

	if (!fwnode)
		return -EINVAL;

	/* USB data support is optional */
	ret = fwnode_property_read_string(fwnode, "data-role", &cap_str);
	if (ret == 0) {
		ret = typec_find_port_data_role(cap_str);
		if (ret < 0)
			return ret;
		port->typec_caps.data = ret;
	}

	ret = fwnode_property_read_string(fwnode, "power-role", &cap_str);
	if (ret < 0)
		return ret;

	ret = typec_find_port_power_role(cap_str);
	if (ret < 0)
		return ret;
	port->typec_caps.type = ret;
	port->port_type = port->typec_caps.type;

	if (port->port_type == TYPEC_PORT_SNK)
		goto sink;

	/* Get source pdos */
	ret = fwnode_property_count_u32(fwnode, "source-pdos");
	if (ret <= 0)
		return -EINVAL;

	port->nr_src_pdo = min(ret, PDO_MAX_OBJECTS);
	ret = fwnode_property_read_u32_array(fwnode, "source-pdos",
					     port->src_pdo, port->nr_src_pdo);
	if ((ret < 0) || tcpm_validate_caps(port, port->src_pdo,
					    port->nr_src_pdo))
		return -EINVAL;

	if (port->port_type == TYPEC_PORT_SRC)
		return 0;

	/* Get the preferred power role for DRP */
	ret = fwnode_property_read_string(fwnode, "try-power-role", &cap_str);
	if (ret < 0)
		return ret;

	port->typec_caps.prefer_role = typec_find_power_role(cap_str);
	if (port->typec_caps.prefer_role < 0)
		return -EINVAL;
sink:
	/* Get sink pdos */
	ret = fwnode_property_count_u32(fwnode, "sink-pdos");
	if (ret <= 0)
		return -EINVAL;

	port->nr_snk_pdo = min(ret, PDO_MAX_OBJECTS);
	ret = fwnode_property_read_u32_array(fwnode, "sink-pdos",
					     port->snk_pdo, port->nr_snk_pdo);
	if ((ret < 0) || tcpm_validate_caps(port, port->snk_pdo,
					    port->nr_snk_pdo))
		return -EINVAL;

	if (fwnode_property_read_u32(fwnode, "op-sink-microwatt", &mw) < 0)
		return -EINVAL;
	port->operating_snk_mw = mw / 1000;

	port->self_powered = fwnode_property_read_bool(fwnode, "self-powered");

	return 0;
}