#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlxsw_sp_rif {TYPE_1__* dev; } ;
struct TYPE_2__ {int ifindex; } ;

/* Variables and functions */

int mlxsw_sp_rif_dev_ifindex(const struct mlxsw_sp_rif *rif)
{
	return rif->dev->ifindex;
}