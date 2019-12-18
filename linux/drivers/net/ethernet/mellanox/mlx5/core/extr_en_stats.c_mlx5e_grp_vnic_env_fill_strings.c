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
struct mlx5e_priv {int /*<<< orphan*/  mdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  format; } ;
struct TYPE_3__ {int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int ETH_GSTRING_LEN ; 
 int NUM_VNIC_ENV_DEV_OOB_COUNTERS (int /*<<< orphan*/ ) ; 
 int NUM_VNIC_ENV_STEER_COUNTERS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* vnic_env_stats_dev_oob_desc ; 
 TYPE_1__* vnic_env_stats_steer_desc ; 

__attribute__((used)) static int mlx5e_grp_vnic_env_fill_strings(struct mlx5e_priv *priv, u8 *data,
					   int idx)
{
	int i;

	for (i = 0; i < NUM_VNIC_ENV_STEER_COUNTERS(priv->mdev); i++)
		strcpy(data + (idx++) * ETH_GSTRING_LEN,
		       vnic_env_stats_steer_desc[i].format);

	for (i = 0; i < NUM_VNIC_ENV_DEV_OOB_COUNTERS(priv->mdev); i++)
		strcpy(data + (idx++) * ETH_GSTRING_LEN,
		       vnic_env_stats_dev_oob_desc[i].format);
	return idx;
}