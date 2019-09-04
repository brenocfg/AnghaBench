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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_flow_handle {int dummy; } ;
struct mlx5_eswitch {int dummy; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 struct mlx5_flow_handle* __esw_fdb_set_vport_rule (struct mlx5_eswitch*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eth_broadcast_addr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mlx5_flow_handle *
esw_fdb_set_vport_rule(struct mlx5_eswitch *esw, u8 mac[ETH_ALEN], u32 vport)
{
	u8 mac_c[ETH_ALEN];

	eth_broadcast_addr(mac_c);
	return __esw_fdb_set_vport_rule(esw, vport, false, mac_c, mac);
}