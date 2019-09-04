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
struct sh_tmu_device {int num_channels; TYPE_1__* pdev; int /*<<< orphan*/  model; } ;
struct device_node {int dummy; } ;
struct TYPE_4__ {struct device_node* of_node; } ;
struct TYPE_3__ {TYPE_2__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SH_TMU ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 

__attribute__((used)) static int sh_tmu_parse_dt(struct sh_tmu_device *tmu)
{
	struct device_node *np = tmu->pdev->dev.of_node;

	tmu->model = SH_TMU;
	tmu->num_channels = 3;

	of_property_read_u32(np, "#renesas,channels", &tmu->num_channels);

	if (tmu->num_channels != 2 && tmu->num_channels != 3) {
		dev_err(&tmu->pdev->dev, "invalid number of channels %u\n",
			tmu->num_channels);
		return -EINVAL;
	}

	return 0;
}