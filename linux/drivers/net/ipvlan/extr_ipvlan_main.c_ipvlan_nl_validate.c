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
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t IFLA_IPVLAN_FLAGS ; 
 size_t IFLA_IPVLAN_MODE ; 
 scalar_t__ IPVLAN_F_PRIVATE ; 
 scalar_t__ IPVLAN_F_VEPA ; 
 scalar_t__ IPVLAN_MODE_MAX ; 
 scalar_t__ nla_get_u16 (struct nlattr*) ; 

__attribute__((used)) static int ipvlan_nl_validate(struct nlattr *tb[], struct nlattr *data[],
			      struct netlink_ext_ack *extack)
{
	if (!data)
		return 0;

	if (data[IFLA_IPVLAN_MODE]) {
		u16 mode = nla_get_u16(data[IFLA_IPVLAN_MODE]);

		if (mode >= IPVLAN_MODE_MAX)
			return -EINVAL;
	}
	if (data[IFLA_IPVLAN_FLAGS]) {
		u16 flags = nla_get_u16(data[IFLA_IPVLAN_FLAGS]);

		/* Only two bits are used at this moment. */
		if (flags & ~(IPVLAN_F_PRIVATE | IPVLAN_F_VEPA))
			return -EINVAL;
		/* Also both flags can't be active at the same time. */
		if ((flags & (IPVLAN_F_PRIVATE | IPVLAN_F_VEPA)) ==
		    (IPVLAN_F_PRIVATE | IPVLAN_F_VEPA))
			return -EINVAL;
	}

	return 0;
}