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
struct TYPE_2__ {int /*<<< orphan*/  regulators; int /*<<< orphan*/  num_regulators; } ;
struct soc_camera_subdev_desc {TYPE_1__ sd_pdata; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int devm_regulator_bulk_get (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int soc_camera_power_init(struct device *dev, struct soc_camera_subdev_desc *ssdd)
{
	/* Should not have any effect in synchronous case */
	return devm_regulator_bulk_get(dev, ssdd->sd_pdata.num_regulators,
				       ssdd->sd_pdata.regulators);
}