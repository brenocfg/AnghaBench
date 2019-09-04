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
typedef  size_t u32 ;
struct TYPE_2__ {int /*<<< orphan*/  trusted; } ;
struct mlx5_vport {int /*<<< orphan*/  enabled; TYPE_1__ info; } ;
struct mlx5_eswitch {int /*<<< orphan*/  dev; struct mlx5_vport* vports; } ;

/* Variables and functions */
 int /*<<< orphan*/  esw_apply_vport_rx_mode (struct mlx5_eswitch*,size_t,int,int) ; 
 int /*<<< orphan*/  esw_debug (int /*<<< orphan*/ ,char*,size_t,int,int) ; 
 int mlx5_query_nic_vport_promisc (int /*<<< orphan*/ ,size_t,int*,int*,int*) ; 

__attribute__((used)) static void esw_update_vport_rx_mode(struct mlx5_eswitch *esw, u32 vport_num)
{
	struct mlx5_vport *vport = &esw->vports[vport_num];
	int promisc_all = 0;
	int promisc_uc = 0;
	int promisc_mc = 0;
	int err;

	err = mlx5_query_nic_vport_promisc(esw->dev,
					   vport_num,
					   &promisc_uc,
					   &promisc_mc,
					   &promisc_all);
	if (err)
		return;
	esw_debug(esw->dev, "vport[%d] context update rx mode promisc_all=%d, all_multi=%d\n",
		  vport_num, promisc_all, promisc_mc);

	if (!vport->info.trusted || !vport->enabled) {
		promisc_uc = 0;
		promisc_mc = 0;
		promisc_all = 0;
	}

	esw_apply_vport_rx_mode(esw, vport_num, promisc_all,
				(promisc_all || promisc_mc));
}