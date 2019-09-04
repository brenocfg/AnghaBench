#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_4__ {scalar_t__ bw_share; } ;
struct TYPE_3__ {scalar_t__ min_rate; scalar_t__ max_rate; } ;
struct mlx5_vport {TYPE_2__ qos; TYPE_1__ info; int /*<<< orphan*/  enabled; } ;
struct mlx5_eswitch {int total_vports; struct mlx5_vport* vports; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ MLX5_CAP_QOS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_MIN_BW_SHARE ; 
 scalar_t__ MLX5_RATE_TO_BW_SHARE (scalar_t__,scalar_t__,scalar_t__) ; 
 int esw_vport_qos_config (struct mlx5_eswitch*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  max_tsar_bw_share ; 

__attribute__((used)) static int normalize_vports_min_rate(struct mlx5_eswitch *esw, u32 divider)
{
	u32 fw_max_bw_share = MLX5_CAP_QOS(esw->dev, max_tsar_bw_share);
	struct mlx5_vport *evport;
	u32 vport_max_rate;
	u32 vport_min_rate;
	u32 bw_share;
	int err;
	int i;

	for (i = 0; i < esw->total_vports; i++) {
		evport = &esw->vports[i];
		if (!evport->enabled)
			continue;
		vport_min_rate = evport->info.min_rate;
		vport_max_rate = evport->info.max_rate;
		bw_share = MLX5_MIN_BW_SHARE;

		if (vport_min_rate)
			bw_share = MLX5_RATE_TO_BW_SHARE(vport_min_rate,
							 divider,
							 fw_max_bw_share);

		if (bw_share == evport->qos.bw_share)
			continue;

		err = esw_vport_qos_config(esw, i, vport_max_rate,
					   bw_share);
		if (!err)
			evport->qos.bw_share = bw_share;
		else
			return err;
	}

	return 0;
}