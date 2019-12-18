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
typedef  int /*<<< orphan*/  val ;
typedef  unsigned int u32 ;
struct mlxsw_sp_nexthop_group {unsigned int count; struct mlxsw_sp_nexthop* nexthops; } ;
struct mlxsw_sp_nexthop {unsigned int ifindex; } ;
struct fib_info {int dummy; } ;
typedef  int /*<<< orphan*/  fi ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned int jhash (unsigned int*,int,unsigned int) ; 
 struct fib_info* mlxsw_sp_nexthop4_group_fi (struct mlxsw_sp_nexthop_group const*) ; 
 int mlxsw_sp_nexthop_group_type (struct mlxsw_sp_nexthop_group const*) ; 

__attribute__((used)) static u32 mlxsw_sp_nexthop_group_hash_obj(const void *data, u32 len, u32 seed)
{
	const struct mlxsw_sp_nexthop_group *nh_grp = data;
	const struct mlxsw_sp_nexthop *nh;
	struct fib_info *fi;
	unsigned int val;
	int i;

	switch (mlxsw_sp_nexthop_group_type(nh_grp)) {
	case AF_INET:
		fi = mlxsw_sp_nexthop4_group_fi(nh_grp);
		return jhash(&fi, sizeof(fi), seed);
	case AF_INET6:
		val = nh_grp->count;
		for (i = 0; i < nh_grp->count; i++) {
			nh = &nh_grp->nexthops[i];
			val ^= jhash(&nh->ifindex, sizeof(nh->ifindex), seed);
		}
		return jhash(&val, sizeof(val), seed);
	default:
		WARN_ON(1);
		return 0;
	}
}