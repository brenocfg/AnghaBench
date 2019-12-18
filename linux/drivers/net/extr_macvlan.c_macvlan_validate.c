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

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 scalar_t__ ETH_ALEN ; 
 size_t IFLA_ADDRESS ; 
 size_t IFLA_MACVLAN_FLAGS ; 
 size_t IFLA_MACVLAN_MACADDR ; 
 size_t IFLA_MACVLAN_MACADDR_COUNT ; 
 size_t IFLA_MACVLAN_MACADDR_MODE ; 
 size_t IFLA_MACVLAN_MODE ; 
 int MACVLAN_FLAG_NOPROMISC ; 
#define  MACVLAN_MACADDR_ADD 136 
#define  MACVLAN_MACADDR_DEL 135 
#define  MACVLAN_MACADDR_FLUSH 134 
#define  MACVLAN_MACADDR_SET 133 
#define  MACVLAN_MODE_BRIDGE 132 
#define  MACVLAN_MODE_PASSTHRU 131 
#define  MACVLAN_MODE_PRIVATE 130 
#define  MACVLAN_MODE_SOURCE 129 
#define  MACVLAN_MODE_VEPA 128 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 int nla_get_u16 (struct nlattr*) ; 
 int nla_get_u32 (struct nlattr*) ; 
 scalar_t__ nla_len (struct nlattr*) ; 

__attribute__((used)) static int macvlan_validate(struct nlattr *tb[], struct nlattr *data[],
			    struct netlink_ext_ack *extack)
{
	if (tb[IFLA_ADDRESS]) {
		if (nla_len(tb[IFLA_ADDRESS]) != ETH_ALEN)
			return -EINVAL;
		if (!is_valid_ether_addr(nla_data(tb[IFLA_ADDRESS])))
			return -EADDRNOTAVAIL;
	}

	if (!data)
		return 0;

	if (data[IFLA_MACVLAN_FLAGS] &&
	    nla_get_u16(data[IFLA_MACVLAN_FLAGS]) & ~MACVLAN_FLAG_NOPROMISC)
		return -EINVAL;

	if (data[IFLA_MACVLAN_MODE]) {
		switch (nla_get_u32(data[IFLA_MACVLAN_MODE])) {
		case MACVLAN_MODE_PRIVATE:
		case MACVLAN_MODE_VEPA:
		case MACVLAN_MODE_BRIDGE:
		case MACVLAN_MODE_PASSTHRU:
		case MACVLAN_MODE_SOURCE:
			break;
		default:
			return -EINVAL;
		}
	}

	if (data[IFLA_MACVLAN_MACADDR_MODE]) {
		switch (nla_get_u32(data[IFLA_MACVLAN_MACADDR_MODE])) {
		case MACVLAN_MACADDR_ADD:
		case MACVLAN_MACADDR_DEL:
		case MACVLAN_MACADDR_FLUSH:
		case MACVLAN_MACADDR_SET:
			break;
		default:
			return -EINVAL;
		}
	}

	if (data[IFLA_MACVLAN_MACADDR]) {
		if (nla_len(data[IFLA_MACVLAN_MACADDR]) != ETH_ALEN)
			return -EINVAL;

		if (!is_valid_ether_addr(nla_data(data[IFLA_MACVLAN_MACADDR])))
			return -EADDRNOTAVAIL;
	}

	if (data[IFLA_MACVLAN_MACADDR_COUNT])
		return -EINVAL;

	return 0;
}