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
struct net_device {int dummy; } ;
struct mlxsw_sp_rif {struct net_device const* dev; } ;

/* Variables and functions */

const struct net_device *mlxsw_sp_rif_dev(const struct mlxsw_sp_rif *rif)
{
	return rif->dev;
}