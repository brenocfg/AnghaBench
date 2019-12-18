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
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sx_port {int dummy; } ;

/* Variables and functions */
 scalar_t__ ETH_HLEN ; 
 scalar_t__ MLXSW_TXHDR_LEN ; 
 int __mlxsw_sx_port_mtu_set (struct mlxsw_sx_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_sx_port_mtu_eth_set(struct mlxsw_sx_port *mlxsw_sx_port,
				     u16 mtu)
{
	mtu += MLXSW_TXHDR_LEN + ETH_HLEN;
	return __mlxsw_sx_port_mtu_set(mlxsw_sx_port, mtu);
}