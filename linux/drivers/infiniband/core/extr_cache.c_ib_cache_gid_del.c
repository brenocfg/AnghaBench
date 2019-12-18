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
struct ib_gid_attr {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 unsigned long GID_ATTR_FIND_MASK_DEFAULT ; 
 unsigned long GID_ATTR_FIND_MASK_GID ; 
 unsigned long GID_ATTR_FIND_MASK_GID_TYPE ; 
 unsigned long GID_ATTR_FIND_MASK_NETDEV ; 
 int _ib_cache_gid_del (struct ib_device*,int /*<<< orphan*/ ,union ib_gid*,struct ib_gid_attr*,unsigned long,int) ; 

int ib_cache_gid_del(struct ib_device *ib_dev, u8 port,
		     union ib_gid *gid, struct ib_gid_attr *attr)
{
	unsigned long mask = GID_ATTR_FIND_MASK_GID	  |
			     GID_ATTR_FIND_MASK_GID_TYPE |
			     GID_ATTR_FIND_MASK_DEFAULT  |
			     GID_ATTR_FIND_MASK_NETDEV;

	return _ib_cache_gid_del(ib_dev, port, gid, attr, mask, false);
}