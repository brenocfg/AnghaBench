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
struct mlx5e_priv {struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {char* board_id; int /*<<< orphan*/  device; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int /*<<< orphan*/  DRIVER_VERSION ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int fw_rev_maj (struct mlx5_core_dev*) ; 
 int fw_rev_min (struct mlx5_core_dev*) ; 
 int fw_rev_sub (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int,int,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void mlx5e_ethtool_get_drvinfo(struct mlx5e_priv *priv,
			       struct ethtool_drvinfo *drvinfo)
{
	struct mlx5_core_dev *mdev = priv->mdev;

	strlcpy(drvinfo->driver, DRIVER_NAME, sizeof(drvinfo->driver));
	strlcpy(drvinfo->version, DRIVER_VERSION,
		sizeof(drvinfo->version));
	snprintf(drvinfo->fw_version, sizeof(drvinfo->fw_version),
		 "%d.%d.%04d (%.16s)",
		 fw_rev_maj(mdev), fw_rev_min(mdev), fw_rev_sub(mdev),
		 mdev->board_id);
	strlcpy(drvinfo->bus_info, dev_name(mdev->device),
		sizeof(drvinfo->bus_info));
}