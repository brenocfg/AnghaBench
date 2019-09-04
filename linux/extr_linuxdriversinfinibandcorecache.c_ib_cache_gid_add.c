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
typedef  union ib_gid {int dummy; } ib_gid ;
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct ib_gid_attr {struct net_device* ndev; } ;
struct ib_device {struct net_device* (* get_netdev ) (struct ib_device*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EPERM ; 
 unsigned long GID_ATTR_FIND_MASK_GID ; 
 unsigned long GID_ATTR_FIND_MASK_GID_TYPE ; 
 unsigned long GID_ATTR_FIND_MASK_NETDEV ; 
 int __ib_cache_gid_add (struct ib_device*,int /*<<< orphan*/ ,union ib_gid*,struct ib_gid_attr*,unsigned long,int) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  make_default_gid (struct net_device*,union ib_gid*) ; 
 int /*<<< orphan*/  memcmp (union ib_gid*,union ib_gid*,int) ; 
 struct net_device* stub1 (struct ib_device*,int /*<<< orphan*/ ) ; 

int ib_cache_gid_add(struct ib_device *ib_dev, u8 port,
		     union ib_gid *gid, struct ib_gid_attr *attr)
{
	struct net_device *idev;
	unsigned long mask;
	int ret;

	if (ib_dev->get_netdev) {
		idev = ib_dev->get_netdev(ib_dev, port);
		if (idev && attr->ndev != idev) {
			union ib_gid default_gid;

			/* Adding default GIDs in not permitted */
			make_default_gid(idev, &default_gid);
			if (!memcmp(gid, &default_gid, sizeof(*gid))) {
				dev_put(idev);
				return -EPERM;
			}
		}
		if (idev)
			dev_put(idev);
	}

	mask = GID_ATTR_FIND_MASK_GID |
	       GID_ATTR_FIND_MASK_GID_TYPE |
	       GID_ATTR_FIND_MASK_NETDEV;

	ret = __ib_cache_gid_add(ib_dev, port, gid, attr, mask, false);
	return ret;
}