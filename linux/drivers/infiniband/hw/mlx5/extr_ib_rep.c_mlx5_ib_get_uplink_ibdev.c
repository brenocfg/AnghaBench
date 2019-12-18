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
struct mlx5_ib_dev {int dummy; } ;
struct mlx5_eswitch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REP_IB ; 
 struct mlx5_ib_dev* mlx5_eswitch_uplink_get_proto_dev (struct mlx5_eswitch*,int /*<<< orphan*/ ) ; 

struct mlx5_ib_dev *mlx5_ib_get_uplink_ibdev(struct mlx5_eswitch *esw)
{
	return mlx5_eswitch_uplink_get_proto_dev(esw, REP_IB);
}