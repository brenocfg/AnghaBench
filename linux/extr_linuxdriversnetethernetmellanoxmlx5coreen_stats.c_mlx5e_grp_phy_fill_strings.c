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
struct TYPE_2__ {char* format; } ;

/* Variables and functions */
 int ETH_GSTRING_LEN ; 
 int /*<<< orphan*/  MLX5_CAP_PCAM_FEATURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NUM_PPORT_PHY_STATISTICAL_COUNTERS ; 
 int /*<<< orphan*/  ppcnt_statistical_group ; 
 TYPE_1__* pport_phy_statistical_stats_desc ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int mlx5e_grp_phy_fill_strings(struct mlx5e_priv *priv, u8 *data,
				      int idx)
{
	int i;

	strcpy(data + (idx++) * ETH_GSTRING_LEN, "link_down_events_phy");

	if (!MLX5_CAP_PCAM_FEATURE((priv)->mdev, ppcnt_statistical_group))
		return idx;

	for (i = 0; i < NUM_PPORT_PHY_STATISTICAL_COUNTERS; i++)
		strcpy(data + (idx++) * ETH_GSTRING_LEN,
		       pport_phy_statistical_stats_desc[i].format);
	return idx;
}