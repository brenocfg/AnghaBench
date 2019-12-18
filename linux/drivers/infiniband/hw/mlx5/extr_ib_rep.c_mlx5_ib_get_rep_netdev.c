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
struct net_device {int dummy; } ;
struct mlx5_eswitch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REP_ETH ; 
 struct net_device* mlx5_eswitch_get_proto_dev (struct mlx5_eswitch*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct net_device *mlx5_ib_get_rep_netdev(struct mlx5_eswitch *esw,
					  u16 vport_num)
{
	return mlx5_eswitch_get_proto_dev(esw, vport_num, REP_ETH);
}