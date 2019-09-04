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
typedef  union mlxsw_sp_l3addr {int dummy; } mlxsw_sp_l3addr ;
typedef  int /*<<< orphan*/  u16 ;
struct netlink_ext_ack {int dummy; } ;
struct ip_tunnel_parm {scalar_t__ link; } ;
struct mlxsw_sp_ipip_entry {struct ip_tunnel_parm parms4; int /*<<< orphan*/  ol_dev; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_SP_L3_PROTO_IPV4 ; 
 int __mlxsw_sp_ipip_entry_update_tunnel (struct mlxsw_sp*,struct mlxsw_sp_ipip_entry*,int,int,int,struct netlink_ext_ack*) ; 
 scalar_t__ mlxsw_sp_ipip_demote_tunnel_by_saddr (struct mlxsw_sp*,int /*<<< orphan*/ ,union mlxsw_sp_l3addr,int /*<<< orphan*/ ,struct mlxsw_sp_ipip_entry*) ; 
 int /*<<< orphan*/  mlxsw_sp_ipip_dev_ul_tb_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_ipip_entry_demote_tunnel (struct mlxsw_sp*,struct mlxsw_sp_ipip_entry*) ; 
 struct ip_tunnel_parm mlxsw_sp_ipip_netdev_parms4 (int /*<<< orphan*/ ) ; 
 union mlxsw_sp_l3addr mlxsw_sp_ipip_parms4_daddr (struct ip_tunnel_parm) ; 
 scalar_t__ mlxsw_sp_ipip_parms4_ikey (struct ip_tunnel_parm) ; 
 scalar_t__ mlxsw_sp_ipip_parms4_okey (struct ip_tunnel_parm) ; 
 union mlxsw_sp_l3addr mlxsw_sp_ipip_parms4_saddr (struct ip_tunnel_parm) ; 
 int /*<<< orphan*/  mlxsw_sp_l3addr_eq (union mlxsw_sp_l3addr*,union mlxsw_sp_l3addr*) ; 

__attribute__((used)) static int
mlxsw_sp_ipip_ol_netdev_change_gre4(struct mlxsw_sp *mlxsw_sp,
				    struct mlxsw_sp_ipip_entry *ipip_entry,
				    struct netlink_ext_ack *extack)
{
	union mlxsw_sp_l3addr old_saddr, new_saddr;
	union mlxsw_sp_l3addr old_daddr, new_daddr;
	struct ip_tunnel_parm new_parms;
	bool update_tunnel = false;
	bool update_decap = false;
	bool update_nhs = false;
	int err = 0;

	new_parms = mlxsw_sp_ipip_netdev_parms4(ipip_entry->ol_dev);

	new_saddr = mlxsw_sp_ipip_parms4_saddr(new_parms);
	old_saddr = mlxsw_sp_ipip_parms4_saddr(ipip_entry->parms4);
	new_daddr = mlxsw_sp_ipip_parms4_daddr(new_parms);
	old_daddr = mlxsw_sp_ipip_parms4_daddr(ipip_entry->parms4);

	if (!mlxsw_sp_l3addr_eq(&new_saddr, &old_saddr)) {
		u16 ul_tb_id = mlxsw_sp_ipip_dev_ul_tb_id(ipip_entry->ol_dev);

		/* Since the local address has changed, if there is another
		 * tunnel with a matching saddr, both need to be demoted.
		 */
		if (mlxsw_sp_ipip_demote_tunnel_by_saddr(mlxsw_sp,
							 MLXSW_SP_L3_PROTO_IPV4,
							 new_saddr, ul_tb_id,
							 ipip_entry)) {
			mlxsw_sp_ipip_entry_demote_tunnel(mlxsw_sp, ipip_entry);
			return 0;
		}

		update_tunnel = true;
	} else if ((mlxsw_sp_ipip_parms4_okey(ipip_entry->parms4) !=
		    mlxsw_sp_ipip_parms4_okey(new_parms)) ||
		   ipip_entry->parms4.link != new_parms.link) {
		update_tunnel = true;
	} else if (!mlxsw_sp_l3addr_eq(&new_daddr, &old_daddr)) {
		update_nhs = true;
	} else if (mlxsw_sp_ipip_parms4_ikey(ipip_entry->parms4) !=
		   mlxsw_sp_ipip_parms4_ikey(new_parms)) {
		update_decap = true;
	}

	if (update_tunnel)
		err = __mlxsw_sp_ipip_entry_update_tunnel(mlxsw_sp, ipip_entry,
							  true, true, true,
							  extack);
	else if (update_nhs)
		err = __mlxsw_sp_ipip_entry_update_tunnel(mlxsw_sp, ipip_entry,
							  false, false, true,
							  extack);
	else if (update_decap)
		err = __mlxsw_sp_ipip_entry_update_tunnel(mlxsw_sp, ipip_entry,
							  false, false, false,
							  extack);

	ipip_entry->parms4 = new_parms;
	return err;
}