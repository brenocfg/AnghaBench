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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_2__ {unsigned long* lp_advertising; } ;
struct ethtool_link_ksettings {TYPE_1__ link_modes; } ;

/* Variables and functions */
 int MLX5_CAP_PCAM_FEATURE (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptys2ethtool_adver_link (unsigned long*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ptys_extended_ethernet ; 

__attribute__((used)) static void get_lp_advertising(struct mlx5_core_dev *mdev, u32 eth_proto_lp,
			       struct ethtool_link_ksettings *link_ksettings)
{
	unsigned long *lp_advertising = link_ksettings->link_modes.lp_advertising;
	bool ext = MLX5_CAP_PCAM_FEATURE(mdev, ptys_extended_ethernet);

	ptys2ethtool_adver_link(lp_advertising, eth_proto_lp, ext);
}