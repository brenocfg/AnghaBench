#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_7__ {TYPE_2__ sin_addr; } ;
struct TYPE_5__ {scalar_t__ sa_family; } ;
union vxlan_addr {TYPE_4__ sin6; TYPE_3__ sin; TYPE_1__ sa; } ;
union mlxsw_sp_l3addr {int /*<<< orphan*/  addr6; int /*<<< orphan*/  addr4; } ;
typedef  enum mlxsw_sp_l3proto { ____Placeholder_mlxsw_sp_l3proto } mlxsw_sp_l3proto ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int MLXSW_SP_L3_PROTO_IPV4 ; 
 int MLXSW_SP_L3_PROTO_IPV6 ; 

__attribute__((used)) static void
mlxsw_sp_switchdev_vxlan_addr_convert(const union vxlan_addr *vxlan_addr,
				      enum mlxsw_sp_l3proto *proto,
				      union mlxsw_sp_l3addr *addr)
{
	if (vxlan_addr->sa.sa_family == AF_INET) {
		addr->addr4 = vxlan_addr->sin.sin_addr.s_addr;
		*proto = MLXSW_SP_L3_PROTO_IPV4;
	} else {
		addr->addr6 = vxlan_addr->sin6.sin6_addr;
		*proto = MLXSW_SP_L3_PROTO_IPV6;
	}
}