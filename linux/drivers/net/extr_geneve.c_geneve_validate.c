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
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
typedef  enum ifla_geneve_df { ____Placeholder_ifla_geneve_df } ifla_geneve_df ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int ERANGE ; 
 scalar_t__ ETH_ALEN ; 
 int GENEVE_DF_MAX ; 
 scalar_t__ GENEVE_N_VID ; 
 size_t IFLA_ADDRESS ; 
 size_t IFLA_GENEVE_DF ; 
 size_t IFLA_GENEVE_ID ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_ATTR (struct netlink_ext_ack*,struct nlattr*,char*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 scalar_t__ nla_get_u32 (struct nlattr*) ; 
 int nla_get_u8 (struct nlattr*) ; 
 scalar_t__ nla_len (struct nlattr*) ; 

__attribute__((used)) static int geneve_validate(struct nlattr *tb[], struct nlattr *data[],
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

	if (!data) {
		NL_SET_ERR_MSG(extack,
			       "Not enough attributes provided to perform the operation");
		return -EINVAL;
	}

	if (data[IFLA_GENEVE_ID]) {
		__u32 vni =  nla_get_u32(data[IFLA_GENEVE_ID]);

		if (vni >= GENEVE_N_VID) {
			NL_SET_ERR_MSG_ATTR(extack, data[IFLA_GENEVE_ID],
					    "Geneve ID must be lower than 16777216");
			return -ERANGE;
		}
	}

	if (data[IFLA_GENEVE_DF]) {
		enum ifla_geneve_df df = nla_get_u8(data[IFLA_GENEVE_DF]);

		if (df < 0 || df > GENEVE_DF_MAX) {
			NL_SET_ERR_MSG_ATTR(extack, tb[IFLA_GENEVE_DF],
					    "Invalid DF attribute");
			return -EINVAL;
		}
	}

	return 0;
}