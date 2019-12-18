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
typedef  int /*<<< orphan*/  u32 ;
struct ptys2ethtool_config {int dummy; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct ptys2ethtool_config*) ; 
 int MLX5_CAP_PCAM_FEATURE (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 struct ptys2ethtool_config* ptys2ext_ethtool_table ; 
 struct ptys2ethtool_config* ptys2legacy_ethtool_table ; 
 int /*<<< orphan*/  ptys_extended_ethernet ; 

__attribute__((used)) static void mlx5e_ethtool_get_speed_arr(struct mlx5_core_dev *mdev,
					struct ptys2ethtool_config **arr,
					u32 *size)
{
	bool ext = MLX5_CAP_PCAM_FEATURE(mdev, ptys_extended_ethernet);

	*arr = ext ? ptys2ext_ethtool_table : ptys2legacy_ethtool_table;
	*size = ext ? ARRAY_SIZE(ptys2ext_ethtool_table) :
		      ARRAY_SIZE(ptys2legacy_ethtool_table);
}