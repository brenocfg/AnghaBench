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
struct net_device {int dummy; } ;
struct macvlan_dev {int mode; int flags; int /*<<< orphan*/  lowerdev; int /*<<< orphan*/  port; } ;
typedef  enum macvlan_mode { ____Placeholder_macvlan_mode } macvlan_mode ;
typedef  enum macvlan_macaddr_mode { ____Placeholder_macvlan_macaddr_mode } macvlan_macaddr_mode ;
typedef  int __u16 ;

/* Variables and functions */
 int EINVAL ; 
 size_t IFLA_MACVLAN_FLAGS ; 
 size_t IFLA_MACVLAN_MACADDR_MODE ; 
 size_t IFLA_MACVLAN_MODE ; 
 int MACVLAN_FLAG_NOPROMISC ; 
 int MACVLAN_MODE_PASSTHRU ; 
 scalar_t__ MACVLAN_MODE_SOURCE ; 
 int dev_set_promiscuity (int /*<<< orphan*/ ,int) ; 
 int macvlan_changelink_sources (struct macvlan_dev*,int,struct nlattr**) ; 
 int /*<<< orphan*/  macvlan_flush_sources (int /*<<< orphan*/ ,struct macvlan_dev*) ; 
 scalar_t__ macvlan_passthru (int /*<<< orphan*/ ) ; 
 struct macvlan_dev* netdev_priv (struct net_device*) ; 
 int nla_get_u16 (struct nlattr*) ; 
 int nla_get_u32 (struct nlattr*) ; 

__attribute__((used)) static int macvlan_changelink(struct net_device *dev,
			      struct nlattr *tb[], struct nlattr *data[],
			      struct netlink_ext_ack *extack)
{
	struct macvlan_dev *vlan = netdev_priv(dev);
	enum macvlan_mode mode;
	bool set_mode = false;
	enum macvlan_macaddr_mode macmode;
	int ret;

	/* Validate mode, but don't set yet: setting flags may fail. */
	if (data && data[IFLA_MACVLAN_MODE]) {
		set_mode = true;
		mode = nla_get_u32(data[IFLA_MACVLAN_MODE]);
		/* Passthrough mode can't be set or cleared dynamically */
		if ((mode == MACVLAN_MODE_PASSTHRU) !=
		    (vlan->mode == MACVLAN_MODE_PASSTHRU))
			return -EINVAL;
		if (vlan->mode == MACVLAN_MODE_SOURCE &&
		    vlan->mode != mode)
			macvlan_flush_sources(vlan->port, vlan);
	}

	if (data && data[IFLA_MACVLAN_FLAGS]) {
		__u16 flags = nla_get_u16(data[IFLA_MACVLAN_FLAGS]);
		bool promisc = (flags ^ vlan->flags) & MACVLAN_FLAG_NOPROMISC;
		if (macvlan_passthru(vlan->port) && promisc) {
			int err;

			if (flags & MACVLAN_FLAG_NOPROMISC)
				err = dev_set_promiscuity(vlan->lowerdev, -1);
			else
				err = dev_set_promiscuity(vlan->lowerdev, 1);
			if (err < 0)
				return err;
		}
		vlan->flags = flags;
	}
	if (set_mode)
		vlan->mode = mode;
	if (data && data[IFLA_MACVLAN_MACADDR_MODE]) {
		if (vlan->mode != MACVLAN_MODE_SOURCE)
			return -EINVAL;
		macmode = nla_get_u32(data[IFLA_MACVLAN_MACADDR_MODE]);
		ret = macvlan_changelink_sources(vlan, macmode, data);
		if (ret)
			return ret;
	}
	return 0;
}