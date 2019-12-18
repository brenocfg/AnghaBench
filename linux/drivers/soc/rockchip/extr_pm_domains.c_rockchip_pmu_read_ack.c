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
struct rockchip_pmu {TYPE_1__* info; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  ack_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static unsigned int rockchip_pmu_read_ack(struct rockchip_pmu *pmu)
{
	unsigned int val;

	regmap_read(pmu->regmap, pmu->info->ack_offset, &val);
	return val;
}