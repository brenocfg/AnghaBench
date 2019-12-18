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
typedef  int /*<<< orphan*/  uint32_t ;
struct smu_context {int dummy; } ;
typedef  enum smu_clk_type { ____Placeholder_smu_clk_type } smu_clk_type ;

/* Variables and functions */
 int smu_get_dpm_freq_by_index (struct smu_context*,int,int,int /*<<< orphan*/ *) ; 

int smu_get_dpm_level_count(struct smu_context *smu, enum smu_clk_type clk_type,
			    uint32_t *value)
{
	return smu_get_dpm_freq_by_index(smu, clk_type, 0xff, value);
}