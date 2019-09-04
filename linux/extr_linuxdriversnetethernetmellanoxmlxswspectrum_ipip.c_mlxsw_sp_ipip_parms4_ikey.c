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
typedef  int /*<<< orphan*/  u32 ;
struct ip_tunnel_parm {int /*<<< orphan*/  i_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ mlxsw_sp_ipip_parms4_has_ikey (struct ip_tunnel_parm) ; 

__attribute__((used)) static u32 mlxsw_sp_ipip_parms4_ikey(struct ip_tunnel_parm parms)
{
	return mlxsw_sp_ipip_parms4_has_ikey(parms) ?
		be32_to_cpu(parms.i_key) : 0;
}