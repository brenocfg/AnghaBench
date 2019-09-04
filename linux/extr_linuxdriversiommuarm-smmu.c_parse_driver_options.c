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
struct arm_smmu_device {int options; TYPE_1__* dev; } ;
struct TYPE_4__ {int opt; int /*<<< orphan*/  prop; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 TYPE_2__* arm_smmu_options ; 
 int /*<<< orphan*/  dev_notice (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parse_driver_options(struct arm_smmu_device *smmu)
{
	int i = 0;

	do {
		if (of_property_read_bool(smmu->dev->of_node,
						arm_smmu_options[i].prop)) {
			smmu->options |= arm_smmu_options[i].opt;
			dev_notice(smmu->dev, "option %s\n",
				arm_smmu_options[i].prop);
		}
	} while (arm_smmu_options[++i].opt);
}