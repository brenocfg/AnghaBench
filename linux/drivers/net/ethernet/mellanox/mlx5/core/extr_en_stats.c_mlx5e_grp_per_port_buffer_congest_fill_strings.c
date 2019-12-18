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
typedef  int /*<<< orphan*/  u8 ;
struct mlx5e_priv {struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_4__ {char* format; } ;
struct TYPE_3__ {char* format; } ;

/* Variables and functions */
 int ETH_GSTRING_LEN ; 
 int /*<<< orphan*/  MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int NUM_PPORT_PER_TC_CONGEST_PRIO_COUNTERS ; 
 int NUM_PPORT_PER_TC_PRIO_COUNTERS ; 
 int NUM_PPORT_PRIO ; 
 TYPE_2__* pport_per_tc_congest_prio_stats_desc ; 
 TYPE_1__* pport_per_tc_prio_stats_desc ; 
 int /*<<< orphan*/  sbcam_reg ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int mlx5e_grp_per_port_buffer_congest_fill_strings(struct mlx5e_priv *priv,
							  u8 *data, int idx)
{
	struct mlx5_core_dev *mdev = priv->mdev;
	int i, prio;

	if (!MLX5_CAP_GEN(mdev, sbcam_reg))
		return idx;

	for (prio = 0; prio < NUM_PPORT_PRIO; prio++) {
		for (i = 0; i < NUM_PPORT_PER_TC_PRIO_COUNTERS; i++)
			sprintf(data + (idx++) * ETH_GSTRING_LEN,
				pport_per_tc_prio_stats_desc[i].format, prio);
		for (i = 0; i < NUM_PPORT_PER_TC_CONGEST_PRIO_COUNTERS; i++)
			sprintf(data + (idx++) * ETH_GSTRING_LEN,
				pport_per_tc_congest_prio_stats_desc[i].format, prio);
	}

	return idx;
}