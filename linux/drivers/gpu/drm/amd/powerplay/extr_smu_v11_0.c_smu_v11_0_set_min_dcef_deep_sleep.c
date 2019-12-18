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
struct TYPE_2__ {int dcefclk; } ;
struct smu_table_context {TYPE_1__ boot_values; } ;
struct smu_context {int /*<<< orphan*/  pm_enabled; struct smu_table_context smu_table; } ;

/* Variables and functions */
 int EINVAL ; 
 int smu_set_deep_sleep_dcefclk (struct smu_context*,int) ; 

__attribute__((used)) static int smu_v11_0_set_min_dcef_deep_sleep(struct smu_context *smu)
{
	struct smu_table_context *table_context = &smu->smu_table;

	if (!smu->pm_enabled)
		return 0;
	if (!table_context)
		return -EINVAL;

	return smu_set_deep_sleep_dcefclk(smu,
					  table_context->boot_values.dcefclk / 100);
}