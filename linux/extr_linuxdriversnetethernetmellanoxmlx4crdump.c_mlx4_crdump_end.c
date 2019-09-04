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
struct mlx4_fw_crdump {int /*<<< orphan*/  region_crspace; int /*<<< orphan*/  region_fw_health; } ;
struct mlx4_dev {TYPE_1__* persist; } ;
struct TYPE_2__ {struct mlx4_fw_crdump crdump; } ;

/* Variables and functions */
 int /*<<< orphan*/  devlink_region_destroy (int /*<<< orphan*/ ) ; 

void mlx4_crdump_end(struct mlx4_dev *dev)
{
	struct mlx4_fw_crdump *crdump = &dev->persist->crdump;

	devlink_region_destroy(crdump->region_fw_health);
	devlink_region_destroy(crdump->region_crspace);
}