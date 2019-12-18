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
typedef  scalar_t__ u32 ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct ifla_vxlan_port_range {int /*<<< orphan*/  low; int /*<<< orphan*/  high; } ;
typedef  enum ifla_vxlan_df { ____Placeholder_ifla_vxlan_df } ifla_vxlan_df ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int ERANGE ; 
 scalar_t__ ETH_ALEN ; 
 scalar_t__ ETH_MAX_MTU ; 
 scalar_t__ ETH_MIN_MTU ; 
 size_t IFLA_ADDRESS ; 
 size_t IFLA_MTU ; 
 size_t IFLA_VXLAN_DF ; 
 size_t IFLA_VXLAN_ID ; 
 size_t IFLA_VXLAN_PORT_RANGE ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_ATTR (struct netlink_ext_ack*,struct nlattr*,char*) ; 
 int VXLAN_DF_MAX ; 
 scalar_t__ VXLAN_N_VID ; 
 int /*<<< orphan*/  is_valid_ether_addr (struct ifla_vxlan_port_range*) ; 
 struct ifla_vxlan_port_range* nla_data (struct nlattr*) ; 
 scalar_t__ nla_get_u32 (struct nlattr*) ; 
 int nla_get_u8 (struct nlattr*) ; 
 scalar_t__ nla_len (struct nlattr*) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vxlan_validate(struct nlattr *tb[], struct nlattr *data[],
			  struct netlink_ext_ack *extack)
{
	if (tb[IFLA_ADDRESS]) {
		if (nla_len(tb[IFLA_ADDRESS]) != ETH_ALEN) {
			NL_SET_ERR_MSG_ATTR(extack, tb[IFLA_ADDRESS],
					    "Provided link layer address is not Ethernet");
			return -EINVAL;
		}

		if (!is_valid_ether_addr(nla_data(tb[IFLA_ADDRESS]))) {
			NL_SET_ERR_MSG_ATTR(extack, tb[IFLA_ADDRESS],
					    "Provided Ethernet address is not unicast");
			return -EADDRNOTAVAIL;
		}
	}

	if (tb[IFLA_MTU]) {
		u32 mtu = nla_get_u32(tb[IFLA_MTU]);

		if (mtu < ETH_MIN_MTU || mtu > ETH_MAX_MTU) {
			NL_SET_ERR_MSG_ATTR(extack, tb[IFLA_MTU],
					    "MTU must be between 68 and 65535");
			return -EINVAL;
		}
	}

	if (!data) {
		NL_SET_ERR_MSG(extack,
			       "Required attributes not provided to perform the operation");
		return -EINVAL;
	}

	if (data[IFLA_VXLAN_ID]) {
		u32 id = nla_get_u32(data[IFLA_VXLAN_ID]);

		if (id >= VXLAN_N_VID) {
			NL_SET_ERR_MSG_ATTR(extack, tb[IFLA_VXLAN_ID],
					    "VXLAN ID must be lower than 16777216");
			return -ERANGE;
		}
	}

	if (data[IFLA_VXLAN_PORT_RANGE]) {
		const struct ifla_vxlan_port_range *p
			= nla_data(data[IFLA_VXLAN_PORT_RANGE]);

		if (ntohs(p->high) < ntohs(p->low)) {
			NL_SET_ERR_MSG_ATTR(extack, tb[IFLA_VXLAN_PORT_RANGE],
					    "Invalid source port range");
			return -EINVAL;
		}
	}

	if (data[IFLA_VXLAN_DF]) {
		enum ifla_vxlan_df df = nla_get_u8(data[IFLA_VXLAN_DF]);

		if (df < 0 || df > VXLAN_DF_MAX) {
			NL_SET_ERR_MSG_ATTR(extack, tb[IFLA_VXLAN_DF],
					    "Invalid DF attribute");
			return -EINVAL;
		}
	}

	return 0;
}