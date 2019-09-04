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
struct ib_gid_attr {unsigned int gid_type; struct net_device* ndev; } ;
struct ib_device {int dummy; } ;
typedef  int /*<<< orphan*/  gid_attr ;
typedef  enum ib_cache_gid_default_mode { ____Placeholder_ib_cache_gid_default_mode } ib_cache_gid_default_mode ;

/* Variables and functions */
 unsigned long GID_ATTR_FIND_MASK_DEFAULT ; 
 unsigned long GID_ATTR_FIND_MASK_GID_TYPE ; 
 unsigned long GID_ATTR_FIND_MASK_NETDEV ; 
 int IB_CACHE_GID_DEFAULT_MODE_DELETE ; 
 int IB_CACHE_GID_DEFAULT_MODE_SET ; 
 unsigned int IB_GID_TYPE_SIZE ; 
 int /*<<< orphan*/  __ib_cache_gid_add (struct ib_device*,int /*<<< orphan*/ ,union ib_gid*,struct ib_gid_attr*,unsigned long,int) ; 
 int /*<<< orphan*/  _ib_cache_gid_del (struct ib_device*,int /*<<< orphan*/ ,union ib_gid*,struct ib_gid_attr*,unsigned long,int) ; 
 int /*<<< orphan*/  make_default_gid (struct net_device*,union ib_gid*) ; 
 int /*<<< orphan*/  memset (struct ib_gid_attr*,int /*<<< orphan*/ ,int) ; 

void ib_cache_gid_set_default_gid(struct ib_device *ib_dev, u8 port,
				  struct net_device *ndev,
				  unsigned long gid_type_mask,
				  enum ib_cache_gid_default_mode mode)
{
	union ib_gid gid = { };
	struct ib_gid_attr gid_attr;
	unsigned int gid_type;
	unsigned long mask;

	mask = GID_ATTR_FIND_MASK_GID_TYPE |
	       GID_ATTR_FIND_MASK_DEFAULT |
	       GID_ATTR_FIND_MASK_NETDEV;
	memset(&gid_attr, 0, sizeof(gid_attr));
	gid_attr.ndev = ndev;

	for (gid_type = 0; gid_type < IB_GID_TYPE_SIZE; ++gid_type) {
		if (1UL << gid_type & ~gid_type_mask)
			continue;

		gid_attr.gid_type = gid_type;

		if (mode == IB_CACHE_GID_DEFAULT_MODE_SET) {
			make_default_gid(ndev, &gid);
			__ib_cache_gid_add(ib_dev, port, &gid,
					   &gid_attr, mask, true);
		} else if (mode == IB_CACHE_GID_DEFAULT_MODE_DELETE) {
			_ib_cache_gid_del(ib_dev, port, &gid,
					  &gid_attr, mask, true);
		}
	}
}