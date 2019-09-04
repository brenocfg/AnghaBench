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
typedef  int /*<<< orphan*/  u8 ;
struct mlx5e_priv {int /*<<< orphan*/  mdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int ETH_GSTRING_LEN ; 
 int /*<<< orphan*/  MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NUM_VNIC_ENV_COUNTERS ; 
 int /*<<< orphan*/  nic_receive_steering_discard ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* vnic_env_stats_desc ; 

__attribute__((used)) static int mlx5e_grp_vnic_env_fill_strings(struct mlx5e_priv *priv, u8 *data,
					   int idx)
{
	int i;

	if (!MLX5_CAP_GEN(priv->mdev, nic_receive_steering_discard))
		return idx;

	for (i = 0; i < NUM_VNIC_ENV_COUNTERS; i++)
		strcpy(data + (idx++) * ETH_GSTRING_LEN,
		       vnic_env_stats_desc[i].format);
	return idx;
}